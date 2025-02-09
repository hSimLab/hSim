# CLI11: Command Line Input argument parser library
CPMAddPackage(
  NAME CLI11
  GITHUB_REPOSITORY CLIUtils/CLI11
  GIT_TAG v2.4.2
  EXCLUDE_FROM_ALL True
)

# fmt: Format Library
CPMAddPackage(
  NAME fmt
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 11.1.3 
  EXCLUDE_FROM_ALL True
)

# elfio: ELF Loader Library
CPMAddPackage(
  NAME elfio
  GITHUB_REPOSITORY serge1/ELFIO
  GIT_TAG Release_3.12
  EXCLUDE_FROM_ALL True
)