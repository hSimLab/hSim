# hSim

Hi there. We introduce high perfomance CPU simulator model.

## How to build
### Requirements
* c++20-compatible compiler (tested on clang++ 18.1.3, g++ 13.3.0, but a bit older compilers seems to be ok)
* CMake 3.19
* Ruby 3.0
* Build is tested on Ubuntu 24.04

To build:
```bash
cmake -S <path_to_repo_root> -B <path_to_build> [-G Ninja]
cmake --build <path_to_build> --parallel <amount_of_jobs>
```
Ninja is optional, but it looks really pretty
After build, you can run our simulator and get some help info
```bash
./build/hSim --help
```


