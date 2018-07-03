# FracMap

Cross-platform software for simulating carbon pseudo-fractal agglomerates and analyzing their morphological properties.

## Getting Started

### Prerequisites

_GUI is a work-in-progress_

> #### FracMAP GUI
> Download, build, and compile wxWidgets. The latest release can be found at:
> https://github.com/wxWidgets/wxWidgets/releases

> Please install wxWidgets in the root folder:

>     Windows: C:/wxWidgets

>     Linux: /wxWidgets

> If installing elsewhere, redirect the project dependencies to the chosen location.

### Installing

_Currently, only the Linux Makefile has been updated to the changes in this fork_

> #### Windows Install
> Microsoft Visual Studio (MSV) 2005 workspace and project files have been included in the source code distribution.
> **To build executable:**
> 1) Open the Microsoft Visual Studio Solution file `Unix_Fractal.sln` from within MSV.
> 2) Select Build -> Build Unix\_Fractal\_final.
> You will find `Unix_Fractal.exe` to the `./debug` directory.

#### Linux Install

##### FracMAP Command Line Interface 

Included with the source code should be the makefile, `Makefile`.

Change directory to `./Unix_Fractal/fractal` where the makefile and base code should be found.

Execute on the command line:

```
make -f Makefile
```

The build should create the executable file `fracmap` in the same directory, `./Unix_Fractal/fractal`.

### Executing

#### Method 1: Without command line arguments

From the command line, execution without parameters (accomplished by double-clicking the executable in Windows):
**You can either:**

1) Double click the file in <del>Windows or</del> Linux.

or

2) Execute on the command line from the `./Unix_Fractal/fractal` directory.

```
./fracmap
```

This method will prompt the user for the expected parameters for fractal creation program.

The program will proceed as follows:

```
Fractal Dimension (decimal value within [1.0, 3.0])
: <Type the value and hit enter>

Prefactor (decimal value within [1.0, inf) )
: <Type the value and hit enter>

Monomer count (integer value greater than 0)
: <Type the value and hit enter>

Overlap Factor (decimal value within [0.5, 1.0] )
: <Type the value and hit enter>

```

**Example:**
```
Fractal Dimension (decimal value within [1.0, 3.0])
: 2.3

Prefactor (decimal value within [1.0, inf) )
: 45.4

Monomer count (integer value greater than 0)
: 21

Overlap Factor (decimal value within [0.5, 1.0] )
: 0.6
```

#### Method 2: With command line arguments.

Run `./fracmap -h` to print the usage comment shown below.


```

	fracMAP v07.03.18

Usage:

	./fracmap [Options]


Inline Command Arguments (program will prompt in absence)

 Fractal Dimension
  -d <fractal dimension> --fractal_dimension <fractal dimension>
  Expects decimal value with the range of [1.0, 3.0]

 Prefactor
  -p <prefactor> --prefactor <prefactor>
  Expects decimal value with the range of [1.0, inf)

 Monomer Count
  -n <monomer count> --monomers <monomer count>
  Expects integer value greater than 0

 Overlap Factor
  -k <overlap factor> --overlap <overlap factor>
  Expects decimal value with the range of [0.5, 1.0]

 Epsilon
  -e <epsilon> --epsilon <epsilon>
  Expects decimal value with the range of (0.0, inf)

 Defaults
  -f --defaults
  Automatically use parameter defaults if not explicitly set in CLI argument.


BATCH: 

 Runs
  -r <number runs> --runs <number runs>
 Run FracMAP a number of times with the same parameters. Expects integer greater than 0.


OUTPUT:

 Verbose
  -b --verbose
  Verbose output

 Monomer XYZ Output
  -o <destination> --vec_output <destination>
  Log monomer XYZ centers to file.

 Run result filename
  -t <destination> --run_dir <destination>
  Choose filename to output run result. Program puts file in ./run_output Defaults to run.txt


MISC:

 Help
  -h --help --usage
  Print this help summary page

 Version
  -v --version
  Get program version


EXAMPLES:

  ./fracmap -d 1.8 -p 3.4 -n 13 -k 0.8 -o out.txt

  ./fracmap --fractal_dimension 2.4 --output output.txt -b

```

#### Execution continued..

Following successful fractal generation, the program will request user input for any
proceeding analysis to be done.

```
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

The user is prompted for the filname of the output file that the program will write the results of a comprehensive analysis of 25 projected, pixelated, 2-D images of the unique stabe orientations of the given 3-D fractal.

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

* [wxWidgets](https://github.com/wxWidgets/wxWidgets) - The cross-platform GUI library used.

## License

This project is licensed under the GPL-2.0 License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

* Credit to the Rajan K. Chakrabarty, Mark A. Garro, Shammah Chancellor, Christopher Herald, and Hans MoosMuller for releasing the first iteration of FracMAP in 2009. [source code](http://cpc.cs.qub.ac.uk/summaries/AEDD_v1_0.html) ["FracMAP: A user-interactive package for performing simulation and orientation-specific morphology analysis of fractal-like solid nano-allglomerates"](https://www.sciencedirect.com/science/article/pii/S0010465509000411?_rdoc=1&_fmt=high&_origin=gateway&_docanchor=&md5=b8429449ccfc9c30159a5f9aeaa92ffb)

* Credit to [Mark Garro](https://github.com/garromark) for improving the source code and giving the simulation a GUI. [GitHub repo](https://github.com/garromark/fracmap) This project is a fork of Mark's repo.
