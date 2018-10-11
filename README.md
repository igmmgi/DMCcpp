# DMCfun 

Cpp command line implementation of the diffusion process model (Diffusion Model
for Conflict Tasks, DMC) presented in Automatic and controlled stimulus
processing in conflict tasks: Superimposed diffusion processes and delta
functions
(https://www.sciencedirect.com/science/article/pii/S0010028515000195). 

NB. See also R/Cpp package DMCfun for further functionality including fitting
procedures.

## Installation
git clone https://github.com/igmmgi/DMCcpp.git

cd DMCcpp
cmake build .
make

## Basic Examples
```cpp
./dmcSim --help

./dmcSim
./dmcSim --tau 150
```
