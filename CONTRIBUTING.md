# Contributing to Heuclid

Thank you for your interest in contributing to Heuclid!

## Development Setup

```bash
git clone --recursive https://github.com/Mr-tooth/Heuclid.git
cd Heuclid
cmake -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build
```

## Code Style

- C++11 standard
- Google-style formatting (see `.clang-format`)
- All public APIs must have Doxygen documentation
- Run `clang-format` before committing

## Pull Request Process

1. Fork and create a feature branch from `master`
2. Ensure all tests pass: `ctest --test-dir build`
3. Add tests for new functionality
4. Update documentation (Doxygen comments)
5. Submit PR with clear description

## Commit Messages

Follow [Conventional Commits](https://www.conventionalcommits.org/):

- `feat:` new feature
- `fix:` bug fix
- `docs:` documentation only
- `build:` build system changes
- `test:` test additions/changes
- `refactor:` code restructuring

## License

By contributing, you agree that your contributions will be licensed under the Apache License 2.0.
