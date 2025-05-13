## skelBMLatmos
PUT AN OVERVIEW OF THE MODULE LIBRARY HERE

### Installation

#### Requirements

- The [R environment](https://cran.r-project.org/).
- On Windows, a version of [Rtools](https://cran.r-project.org/bin/windows/Rtools/)
  appropriate for your version of R.
- On Linux, gcc and g++ version 4.9.3 or greater (consult documentation for your
  distribution for installation instructions).
- On MacOS, Xcode.

#### Installation steps

First, obtain a local copy of this repository, which can be accomplished using
either of two methods:
1. If you are new to Git, the easiest way to get a local copy is to install
   GitHub Desktop and use the "Open with GitHub Desktop option in the "Code"
   dropdown on the GitHub repository page.
2. Alternatively, clone this repository using Git on the command line in the
   usual fashion by running `git clone <repository URL>` where
   `<repository URL>` is the URL for this repository. This repository contains a
   Git submodule, so you will need to take the additional step of running
   `git submodule update --init` to obtain it.

After obtaining a local copy of the source code, install the package from the
command line or from within R using one of the following sets of commands. These
assume that the source files are in a directory named  'skelBMLatmos'.

- From the command line
```
cd path_to_unzipped_directory
R CMD INSTALL skelBMLatmos
```

- Or from within R
```
setwd('path_to_unzipped_directory')
install.packages('skelBMLatmos', repos=NULL, type='SOURCE')
```

### An example

The following code will print a list of all modules available in this library,
return information about one of them (`example_module`), and then run that
module:

To give manual input:
```
library(BioCro)
library(skelBMLatmos)
get_all_modules('skelBMLatmos')
module_info('skelBMLatmos:example_module')
evaluate_module('skelBMLatmos:example_module',list(To=300.0,Tr=0.8,Ta=0.9,Ion=1000.0,h=0.5,Po=101325.0,BA=0.05,nu=0.3,Ps=0.2))


| Input | Meaning (based on naming)        | Notes                            |
| ----- | -------------------------------  | -------------------------------- |
| `To`  | Some initial temperature (?)     | Kelvin or arbitrary              |
| `Tr`  | Transmission ratio               | Range: 0–1                       |
| `Ta`  | Atmospheric transmission         | Range: 0–1                       |
| `Ion` | Incoming solar radiation         | W/m²                             |
| `h`   | Solar elevation angle (radians)  | Between 0 and π/2 (approx 28.6°) |
| `Po`  | Some pressure value (?)          | Pascals                          |
| `BA`  | Some coefficient                 | Dimensionless                    |
| `nu`  | Scaling coefficient              | Dimensionless                    |
| `Ps`  | Reflection/feedback parameter    | Dimensionless                    |

```

To use inputs.csv file
```
library(skelBMLatmos)
> library(BioCro)
> input_df <- read.csv("inputs.csv")
> if (!"time" %in% names(input_df)) {
+   stop("Input file must contain a 'time' column.")
+ }
> result <- run_biocro(
+   initial_values = list(),
+ parameters = list(timestep = 1),
+ drivers = input_df,
+   direct_module_names = list("skelBMLatmos:example_module"),
+   differential_module_names = list()
+ )
> print(result)
> result[c("time", "P_tilde", "Pb", "PdR", "PdA", "Pas")]

Output Name	Full 
| Output Name  | Full Name                                                                                                                                                                                             
| P\_tilde   |  Modified Transmitted Radiation                    
| Pb         |  Direct Beam Radiation Component                     
| PdR        |  Diffuse Radiation from Reflection                  
| PdA        |  Diffuse Radiation from Absorption                  
| Pas        |  Available Photosynthetically Active Radiation (PAR) 


```
For more information about using BioCro modules in R, please see the
[BioCro framework R package](https://github.com/biocro/biocro).

### Source

This package was derived from the
[BioCro skeleton module library](https://github.com/biocro/skelBML). See
`skelBML_description` for more information about the version of the skeleton
library that was used.

### License

The `skelBMLatmos` R package is licensed under the MIT license, while the BioCro C++
framework is licensed under version 3 or greater of the GNU Lesser General
Public License (LGPL). This scheme allows people to freely develop models for
any use (public or private) under the MIT license, but any changes to the
framework that assembles and solves models must make source code changes
available to all users under the LGPL. See `LICENSE.note` for more details.
