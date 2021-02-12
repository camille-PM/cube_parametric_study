#include<vector>

constexpr int LATTICE_X = 151; 
constexpr int LATTICE_Y = 151;
constexpr int LATTICE_Z = 201; // with sources from above and below for the cells 
constexpr int NODES_PER_ELEM = 10; // number of nodes per element in Abaqus
constexpr float CELL_DIAMETER = 0.02; // (in mm)

struct Point { // lattice point (integer)
	int x, y, z;
};
struct Point_abaqus { // Point coordinates in Abaqus (in mm) - float
	float x, y, z;
};
struct Nodes { // (useful) node indices for a given element
	int n0, n1, n2, n3;
};

int nrand(int n);

int Read_node_file(std::vector<Point_abaqus>& nodes_position);
int Read_element_file(std::vector<Nodes>& nodes_element);
void Prepare_simulation_file(int number_elems);

void Calculate_lattice(std::vector<Nodes>& lattice_element, std::vector<Point_abaqus>& lattice_node_position, float Global_min[3], float Global_max[3]);
void Extremes_element(std::vector<Nodes>& extremes_element_nodes,std::vector<Point_abaqus>& extremes_node_positions,std::vector<Point>& extreme_min,std::vector<Point>& extreme_max, 
	float Global_min_extreme[3],float Global_max_extreme[3]);
void Lattice_point_in_element (char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], std::vector<Point>& element_min, 
	std::vector<Point>& element_max,float Global_min[3], float Global_max[3],std::vector<Point_abaqus>& node_pos,std::vector<Nodes>& elem_nodes);
float Plane_intersection(float face[3][3],float x,float y,float z);
void Initialize_lattice(char initial_lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], short initial_age[LATTICE_X][LATTICE_Y][LATTICE_Z]);
void Read_stimulus(std::vector<char>& stimulus_read, int number_elems);

void Lattice_stimulus (char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], std::vector<char>& stimulus);
float Compute_bone_volume(char objective_lattice[LATTICE_X][LATTICE_Y][LATTICE_Z]);
void Write_text_output(float objective);

