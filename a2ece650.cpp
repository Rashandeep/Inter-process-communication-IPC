#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

vector<vector<int>> edge_matrix;

vector<vector<int>> dummy_edge_matrix;

string delimiter = ",";

vector<string> getSubs(string str)
{
	int x = 0;
	string delimiter1 = "<";
	string delimiter2 = ">";
	vector<string> substrs;
	size_t position = str.find(delimiter1);
	while (position != string::npos)
	{
		int y;
		size_t endPos;
		endPos = str.find(delimiter2, position);
		y = 1;
		if (str.find(delimiter2, position) == string::npos)
			break;
		int a = position + 1;
		int b = endPos - position - 1;
		substrs.push_back(str.substr(a, b));
		y = 0;
		position = str.find('<', endPos);
	}

	return substrs;
}

int main(int argc, char *argv[])
{
	int x = 0;
	while (1)
	{
		char buffer[256];
		buffer[0] = 'q';
		string line = " ";
		if (x < 2)
		{
			getline(cin, line);
			x++;
			cout << line << endl;
		}
		istringstream input(line);
		int vertex;
		if (line[0] == 'V')
		{
			stringstream q1;
			if (line.length() == 3)
			{
				q1 << line[2];
				q1 >> vertex;
			}
			else if (line.length() == 4)
			{
				q1 << line.substr(2, 2);
				q1 >> vertex;
			}
			else
			{
				q1 << line.substr(2, 3);
				q1 >> vertex;
			}
			continue;
		}

		string edges;
		string path;
		int source;
		int destination;

		if (line[0] == 'E')
		{
			if (vertex == 7000)
			{
				cout << "Error: Please enter vertices" << endl;
				continue;
			}
			edge_matrix.clear();
			edges = line.substr(2, line.length());
			for (int a = 0; a < vertex; a++)
			{
				vector<int> temp;
				for (int b = 0; b < vertex; b++)
				{
					temp.push_back(0);
				}
				edge_matrix.push_back(temp);
			}

			int flag = 0;
			vector<string> substrings = getSubs(line);
			for (string s : substrings)
			{
				size_t position = 0;
				int chd;
				string vali;
				chd = 0;
				string v1;
				while ((position = s.find(delimiter)) != std::string::npos)
				{
					vali = s.substr(0, position);
					v1 = vali;
					s.erase(0, position + delimiter.length());
				}
				string v2 = s;

				stringstream st;
				st << v1;
				int v1i;
				st >> v1i;

				stringstream st1;
				st1 << v2;
				int v2i;
				st1 >> v2i;
				if (v1i > vertex - 1 || v2i > vertex - 1)
				{
					flag = 1;
				}
				else
				{
					edge_matrix[v1i][v2i] = 1;
					edge_matrix[v2i][v1i] = 1;
				}
			}

			dummy_edge_matrix = edge_matrix;

			continue;
		}

		else
		{
			int val = (int)*(argv[1]) - 48;

			ssize_t n = read(val, buffer, sizeof(buffer));
			if (buffer[0] == 'q')
			{
				break;
			}

			line = buffer;
			edge_matrix = dummy_edge_matrix;
			int distance_matrix[vertex];

			for (int i = 0; i < vertex; i++)
			{
				distance_matrix[i] = INT_MAX;
			}

			queue<int> qt;
			int previous_vertex[vertex];

			for (int i = 0; i < vertex; i++)
			{
				previous_vertex[i] = INT_MAX;
			}

			size_t position = 0;
			std::string vali;
			string x1;
			while ((position = line.find(' ')) != std::string::npos)
			{
				vali = line.substr(0, position);
				x1 = vali;
				int a = position + delimiter.length();
				line.erase(0, a);
			}
			string x2 = line;

			stringstream p;
			p << x1;
			p >> source;

			stringstream q;
			q << x2;
			q >> destination;

			if (source > vertex - 1 || destination > vertex - 1)
			{
				cout << "Error: The vertex for source or destination provided does not exists" << endl;
				continue;
			}

			int source_dummy;
			int source_dummy2 = source;
			if (source == destination)
			{
				for (int i = 0; i < vertex; i++)
				{
					if (edge_matrix[source][i] == 1)
					{
						edge_matrix[source][i] = 0;
						edge_matrix[i][source] = 0;
						source_dummy = i;
						break;
					}
				}
			}

			if (source == destination)
				source = source_dummy;

			qt.push(source);
			distance_matrix[source] = 0;
			previous_vertex[source] = source;

			while (!qt.empty())
			{
				int node = qt.front();
				int distance = distance_matrix[node];
				for (int i = 0; i < vertex; i++)
				{
					if (edge_matrix[node][i] == 1)
					{
						int new_distance = distance + 1;
						if (new_distance < distance_matrix[i])
						{
							distance_matrix[i] = new_distance;
							previous_vertex[i] = node;
							qt.push(i);
						}
					}
				}
				qt.pop();
			}

			int pointer = previous_vertex[destination];

			if (pointer == INT_MAX)
			{
				cout << "Error: Path doesnot exists" << endl;
				continue;
			}

			int arr[3000];
			int i = 0;
			arr[i] = destination;
			i++;
			arr[i] = pointer;
			i++;
			while (pointer != source)
			{
				pointer = previous_vertex[pointer];
				arr[i] = pointer;
				i++;
			}

			string res = "";

			if (source_dummy2 == destination)
			{
				stringstream temp1;
				temp1 << source_dummy2;
				res = temp1.str() + "-";
			}

			for (int j = i - 1; j >= 0; j--)
			{
				stringstream temp;
				temp << arr[j];
				if (j != 0)
					res = res + temp.str() + "-";
				else
					res = res + temp.str();
			}

			cout << res << endl;
			continue;
		}
		if (input.eof())
		{
			cout << "break";
			break;
		}
	}
	return (0);
}
