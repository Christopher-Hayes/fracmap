# FracMap

Cross-platform software for simulating carbon pseudo-fractal agglomerates and analyzing their morphological properties.

## Getting Started

### Prerequisites

Download, build, and compile wxWidgets. The latest release can be found at:

https://github.com/wxWidgets/wxWidgets/releases


Please install wxWidgets in the root folder:

    Windows: C:/wxWidgets

    Linux: /wxWidgets

If installing elsewhere, redirect the project dependencies to the chosen location.

### Installing

#### Windows Install

Microsoft Visual Studio (MSV) 2005 workspace and project files have been included in
the source code distribution.

**To build executable:**

1) Open the Microsoft Visual Studio Solution file `Unix_Fractal.sln` from within MSV.

2) Select Build->Build Unix_Fractal_final.

You will find `Unix_Fractal.exe` to the `./debug` directory.

#### Linux Install

Included with the source code should be the makefile, `Makefile`.

Change directory to `./Unix_Fractal` where the makefile and base code should be found.

Execute on the command line:

```
make -f Makefile
```

The build should create the executable file `fractal` in the same directory, `./Unix_Fractal/fractal`.

### Executing

#### Method 1: Without command line arguments

From the command line, execution without parameters (accomplished by double-clicking the executable in Windows):
**You can either:**

1) Double click the file in Windows or Linux.

or

2) Execute on the command line from the `./Unix_Fractal` directory.

```
./fractal
```

This method will prompt the user for the expected parameters for fractal creation program.

The program will proceed as follows:

```
Fractal Dimension?
<Type the value and hit enter>

Prefactor?
<Type the value and hit enter>

Fractal Size?
<Type the value and hit enter>
```

**Example:**
```
Fractal Dimension?
2.0

Prefactor?
1.19

Fractal Size?
10
```

#### Method 2: With command line arguments.

Command line execution given specified parameters:

```
./fractal <fractal_dimension> <prefactor> <size>
```

**Example:**
```
./fractal 2.0 1.19 10
```

#### Execution continued..

With both methods, a fractal will be generated with Df equal to `fractal_dimension`,
kf equal to "prefactor", and of size equal to "size".

Following successful fractal generation, the program will request user input for any
proceeding analysis to be done.

```
Fractal Paramters: N = <size>
Choose an option to continue.

Fractal menu:
  0: Exit
  1: Clear current fractal and create a new fractal
  2: Calculate Structure Fractor of Current Fractal
  3: 2D Micrograph Analysis
  4: Help

<Type in the integer of the menu option and hit enter>
```

#### Options

##### Option 0

The program exits.

##### Option 1

The current fractal information is cleared. The user is then prompted for new parameters to construct a new fractal.

##### Option 2

The user is prompted for the filname of the output file that the program will write the lognormal values of Qval and Angsum. The program will separate the values by tabs so that the file can be opened in a spreadsheet management software such as Excel for further analysis. The user must take a linear regression, but must make a decision for preliminary cutoff of output points such that the regression is for the most part, a linear one.

##### Option 3

The user is prompted for the filname of the output file that the program will write the results of a comprehensive analysis of 25 projected, pixelated, @-D images of the unique stabe orientations of the given 3-D fractal.

For each trial, the following parameters are outputted.

**N-projected** - The apparent number of monomer in the 2-D image area of the 2-D image.

**N** - The actual number of monomers in the 2-D image.

**Lmax** - The maximum length (in units, monomer radius is one unit) of the 2-D image.

**width** - The maximum perpendicular width to the given Lmax.

**2-D Fractal Dimension** (Box Counting Method)

**R^2** - The value for the linear regression to find the above value.

**2-D Hybrid Perimeter Fractal Dimension**

**R^2** - The value for the linear regression to find the above value.

**Sorrenson's 2-D Perimeter Fractal Dimension Method**

**R^2** - The value for the linear regression to find the above value.

**3-D Fractal Dimension**

**2-D Radius of Gyration**

**3-D Radius of Gyration**

## Built With

** [wxWidgets](https://github.com/wxWidgets/wxWidgets) - The cross-platform GUI library used.

## License

This project is licensed under the GPL-2.0 License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

** Credit to the Rajan K. Chakrabarty, Mark A. Garro, Shammah Chancellor, Christopher Herald, and Hans MoosMuller for releasing the first iteration of FracMAP in 2009. [source code](http://cpc.cs.qub.ac.uk/summaries/AEDD_v1_0.html) ["FracMAP: A user-interactive package for performing simulation and orientation-specific morphology analysis of fractal-like solid nano-allglomerates"](https://www.sciencedirect.com/science/article/pii/S0010465509000411?_rdoc=1&_fmt=high&_origin=gateway&_docanchor=&md5=b8429449ccfc9c30159a5f9aeaa92ffb)

** Credit to [Mark Garro](https://github.com/garromark) for improving the source code and giving the simulation a GUI. [GitHub repo](https://github.com/garromark/fracmap) This project is a fork of Mark's repo.
