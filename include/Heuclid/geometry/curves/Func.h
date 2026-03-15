#pragma once
/**
 * @file Func.h
 * @brief Template function and Bézier curve classes.
 * @author Junhang Lai (赖俊杭)
 */

#include <array>
#include <cmath>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <vector>
#include <Heuclid/title/Title.h>
#include <Eigen/Dense>
#include <iostream>

_LJH_EUCLID_LIB_BEGIN

/** \brief Mathematical function.
    \tparam T function value type
*/
template<class T>
class Func
{
public:
  /** \brief Constructor. */
  Func() {}

  /** \brief Evaluate function value.
      \param t arugment of function
  */
  virtual T operator()(double t) const = 0;

  /** \brief Evaluate function derivative value.
      \param t arugment of function
      \param order derivative order
  */
  virtual T derivative(double t, int order = 1) const = 0;

  /** \brief Get lower limit of domain. */
  virtual double domainLowerLimit() const
  {
    return std::numeric_limits<double>::lowest();
  }

  /** \brief Get upper limit of domain. */
  virtual double domainUpperLimit() const
  {
    return std::numeric_limits<double>::max();
  }
};

/** \brief Piecewise function.
    \tparam T function value type
*/
template<class T>
class PiecewiseFunc : public Func<T>
{
public:
  /** \brief Constructor. */
  PiecewiseFunc() {}

  /** \brief Evaluate function value.
      \param t arugment of function
  */
  virtual T operator()(double t) const override
  {
    checkArg(t);
    auto funcIt = funcs_.lower_bound(t);
    return (*(funcIt->second))(t);
  }

  /** \brief Evaluate function derivative value.
      \param t arugment of function
      \param order derivative order
  */
  virtual T derivative(double t, int order = 1) const override
  {
    checkArg(t);
    auto funcIt = funcs_.lower_bound(t);
    return (funcIt->second)->derivative(t, order);
  }

  /** \brief Get the index of piecewise functions.
      \param t arugment of function
  */
  virtual size_t index(double t) const
  {
    checkArg(t);
    return std::distance(funcs_.begin(), funcs_.lower_bound(t));
  }

  /** \brief Get lower limit of domain. */
  virtual double domainLowerLimit() const override
  {
    return tLowerLimit_;
  }

  /** \brief Get upper limit of domain. */
  virtual double domainUpperLimit() const override
  {
    if(funcs_.empty())
    {
      return std::numeric_limits<double>::max();
    }
    return funcs_.rbegin()->first;
  }

  /** \brief Clear function. */
  void clearFuncs()
  {
    funcs_.clear();
    tLowerLimit_ = std::numeric_limits<double>::lowest();
  }

  /** \brief Add function.
      \param t upper bound of domain
      \param func function
  */
  void appendFunc(double t, std::shared_ptr<Func<T>> func)
  {
    funcs_.insert(std::pair<double, std::shared_ptr<Func<T>>>(t, func));
  }

  /** \brief Set lower limit of domain
      \param t lower limit of domain
  */
  void setDomainLowerLimit(double t)
  {
    tLowerLimit_ = t;
  }

protected:
  /** \brief Check argument of function.
      \param t arugment of function
  */
  void checkArg(double t) const
  {
    if(t < tLowerLimit_ || funcs_.rbegin()->first < t)
    {
      throw std::runtime_error("[PiecewiseFunc] Argument is out of function range. it should be "
                               + std::to_string(tLowerLimit_) + " <= " + std::to_string(t)
                               + " <= " + std::to_string(funcs_.rbegin()->first));
    }
  }

protected:
  //! Map of upper bound of domain and function
  std::map<double, std::shared_ptr<Func<T>>> funcs_;

  //! Lower limit of domain of this function
  double tLowerLimit_ = std::numeric_limits<double>::lowest();
};

/** \brief Beizer function.
    \tparam T function value type
    \tparam Order order of beizer function
*/

template<class T, int Rows, int Order>
class Bezier : public Func<T>
{
  using controlPointsArray = std::array<T, Order+1>;
  using controlPointsMatrix = Eigen::Matrix<double, Rows, Order+1>;
  
public:
  Bezier()
  {
    

  };
  Bezier(controlPointsArray control_points, double duration, double t0 = 0.0)
  :control_points_(control_points),
   control_points_matrix(Eigen::Map<controlPointsMatrix>(control_points[0].data(), Rows, control_points.size())),
   t0_(t0), 
   duration_(duration)
  {
    this->compute_coeff();
    // for(int i=0; i<Order+1; i++)
    // {
    //   this->control_points_matrix.row(i) = this->control_points_.at(i).transpose();
    // }
    std::cout<<"control_matrix: \n"<<this->control_points_matrix<<std::endl;
    std::cout<<"end";
  }

  void setParams(controlPointsArray control_points, double duration, double t0 = 0.0)
  {
    this->control_points_ = control_points;
    this->control_points_matrix = Eigen::Map<controlPointsMatrix>(control_points[0].data(), Rows, control_points.size());
    this->t0_ = t0;
    this->duration_ = duration;
    this->compute_coeff();
  }

  /** \brief Evaluate function value.
      \param t arugment of function
  */
  virtual T operator()(double t) const override
  {
    T ret;
    ret.setZero();

    double u = (t-this->t0_)/this->duration_;

    for(int i = 0; i<=Order; i++)
    {
      ret += this->B_coeff_.at(i) * std::pow(1 - u, Order - i) * std::pow(u, i)  * this->control_points_.at(i);
    }
    return ret;
  }

  /** \brief Evaluate biezer function value with De Casteljau's Algorithm.
      \param t arugment of function
  */
  T at(double t) const
  {
    double u = (t-this->t0_)/this->duration_;
    
    controlPointsMatrix temp = this->control_points_matrix;
    for(int i = 0; i < Order; ++i)
    {
      for(int j = 0; j < Order - i; ++j)
      {
        temp.col(j) = (1.0 - u) * temp.col(j) + u * temp.col(j+1);
      }
    }
    return temp.col(0);
  }

  /** \brief Evaluate function derivative value.
      \param t arugment of function
      \param derivativeOrder derivative order
  */
  virtual T derivative(double t, int derivativeOrder = 1) const override
  {
    if(derivativeOrder > Order)
    {
      T ret; // Dummy initialization for dynamic size class
      ret.setZero();
      return ret;
    }

    double u = (t-this->t0_)/this->duration_;

    double prefix = 1.0;

    for(int i=0; i<derivativeOrder; ++i) 
      prefix *= Order - i;
    prefix *= std::pow(1.0 / duration_, derivativeOrder);

    controlPointsMatrix temp = this->control_points_matrix;
    
    // reference: https://zhuanlan.zhihu.com/p/130247362
    // 计算 p^{(k)}
    for(int k = 0; k < derivativeOrder; ++k)
    {
        for(int i = 0; i <= Order-k-1; ++i)
        {
            temp.col(i) = temp.col(i+1) - temp.col(i);
        }
    }

    // 2. 计算 C^{(k)}(t) = \sum_{i=0}^{N-k} B_{i,N-k}(t) p^{(k)}
    for(int i = 0; i < Order - derivativeOrder; ++i)
    {
      for(int j = 0; j < Order - derivativeOrder - i; ++j)
      {
        temp.col(j) = (1.0 - u) * temp.col(j) + u * temp.col(j + 1);
      }
    }
    return prefix * temp.col(0);

  }

  void compute_coeff()
  {
    this->B_coeff_.fill(1.0);
    this->dB_coeff_.fill(1.0);

    for(int i = 2; i <= Order; ++i)
    {
      for(int j = i-1; j > 0; --j)
      {
        this->B_coeff_[j] = this->B_coeff_[j] + this->B_coeff_[j-1];
      }
    }

    for(int i = 2; i <= Order-1; ++i)
    {
      for(int j = i-1; j > 0; --j)
      {
        this->dB_coeff_[j] = this->dB_coeff_[j] + this->dB_coeff_[j-1];
      }
    }
  }
protected:

  //! control point from low order to high order
  std::array<T, Order+1> control_points_;

  controlPointsMatrix control_points_matrix;

  //! coefficients
  std::array<double, Order+1> B_coeff_;

  //! dB_coefficients
  std::array<double, Order> dB_coeff_;

  //! offset of function argument  
  double t0_;

  //! the real duration of the traj
  double duration_;

};


/** \brief Polynomial function.
    \tparam T function value type
    \tparam Order order of polynomial function
*/
template<class T, int Order>
class Polynomial : public Func<T>
{
public:
  /** \brief Constructor.
      \param coeff coefficients of polynomial (from low order (i.e., constant term) to high order)
      \param t0 offset of function arugment
  */
  Polynomial(const std::array<T, Order + 1> & coeff, double t0 = 0.0) : coeff_(coeff), t0_(t0) {}

  /** \brief Get polynomial order. */
  int order() const
  {
    return Order;
  }

  /** \brief Evaluate function value.
      \param t arugment of function
  */
  virtual T operator()(double t) const override
  {
    T ret = coeff_[0];
    for(int i = 0; i < Order; i++)
    {
      ret += coeff_[i + 1] * std::pow(t - t0_, i + 1);
    }
    return ret;
  }

  /** \brief Evaluate function derivative value.
      \param t arugment of function
      \param derivativeOrder derivative order
  */
  virtual T derivative(double t, int derivativeOrder = 1) const override
  {
    if(derivativeOrder > Order)
    {
      T ret = coeff_[0]; // Dummy initialization for dynamic size class
      ret.setZero();
      return ret;
    }

    T ret = coeff_[derivativeOrder];
    for(int j = 0; j < derivativeOrder - 1; j++)
    {
      ret *= (derivativeOrder - j);
    }

    for(int i = 0; i < Order - derivativeOrder; i++)
    {
      T term = coeff_[i + 1 + derivativeOrder] * std::pow(t - t0_, i + 1);
      for(int j = 0; j < derivativeOrder; j++)
      {
        term *= (i + 1 + derivativeOrder - j);
      }
      ret += term;
    }

    return ret;
  }

protected:
  //! Coefficients from low order (i.e., constant term) to high order
  std::array<T, Order + 1> coeff_;

  //! Offset of function arugment
  double t0_;
};

/** \brief Constant function.
    \tparam T function value type
*/
template<class T>
class Constant : public Polynomial<T, 0>
{
public:
  /** \brief Constructor.
      \param value constant value
  */
  Constant(const T & value) : Polynomial<T, 0>(std::array<T, 1>{value}) {}

  /** \brief Evaluate function value.
      \param t arugment of function (which does not affect the return value)
  */
  virtual T operator()(double t = 0.0) const override
  {
    return Polynomial<T, 0>::operator()(t);
  }
};

/** \brief Linear polynomial function. */
template<class T>
using LinearPolynomial = Polynomial<T, 1>;

/** \brief Quadratic polynomial function. */
template<class T>
using QuadraticPolynomial = Polynomial<T, 2>;

/** \brief Cubic polynomial function. */
template<class T>
using CubicPolynomial = Polynomial<T, 3>;

_LJH_EUCLID_LIB_END
