#include "gnuplot_i.hpp"
#include <vector>
#include <iostream>

int main()
{
	Gnuplot plotter("steps");
	std::vector<unsigned int> puntix;
	std::vector<unsigned int> puntiy;
	puntix.push_back(1);
	puntix.push_back(3);
	puntix.push_back(4);
	puntix.push_back(7);
	puntix.push_back(9);
	puntiy.push_back(1);
	puntiy.push_back(2);
	puntiy.push_back(3);
	puntiy.push_back(4);
	puntiy.push_back(5);
	plotter.set_style("points");
	plotter.plot_xy(puntix, puntiy, "punti");
	char a = 'a';
	std::cin >> a;
	return 0;
}
