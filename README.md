# cube_parametric_study
Computer framework used in the cubic scaffold parametric study (initial mechanical signals and full regeneration)
Here is the case of the full regeneration study.

**Instructions**
* Put all files in the same folder as the Abaqus CAE file
* Compile C++ code -> "cubic_scaffold.exe" (this is the code for the full regeneration)
* Run "script.m" in MATLAB
* Results will be available in a text file called "optimisation.log": first 7 columns give the values of the pore sizes in x (each layer), y (each layer) and z directions, last column is the corresponding objective value.
