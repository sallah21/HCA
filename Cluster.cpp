#include "Cluster.h"
#include <algorithm>


Cluster::Cluster(Cluster& c1, Cluster& c2  ) { //! konstruktor sumujacy  dwa rozne klastry do jednego nowego 
	this->length = c1.getEntitySize() + c2.getEntitySize();
	std::vector<Entity<double>>v;
	for (int i = 0; i < (c1.getEntitySize() + c2.getEntitySize()); i++) {
		if (i < c1.getEntitySize())
		{
			v.push_back(c1.data.at(i));
		}
		else {
			v.push_back(c2.data.at(i-c1.getEntitySize()));
		}
	}
	this->data = v;
}




double CalculateDistance(const Cluster& c1, const Cluster& c2) //! liczenie odleglosci metoda "Manhatan" 
{
	double dist = 0;
	int counter = 1;
	int A = c1.getEntitySize();
	int B = c2.getEntitySize();
	if (A > B) {
		for (int i = 0; i < B; i++) 
			{ 
			for (int j = 0; j < c1.getEntity().at(i).getSize(); j++)
			{

				dist += abs(c1.getEntity().at(i).getLocation()[j] - c2.getEntity().at(i).getLocation()[j]);
			}
			counter++;
		}
		
	}
	else {

		for (int i = 0; i < A; i++) 
		{
			for (int j = 0; j < c2.getEntity().at(i).getSize(); j++)
			{
				dist += abs(c1.getEntity().at(i).getLocation()[j] - c2.getEntity().at(i).getLocation()[j]);
			}
			counter++;
		}
	}
	return sqrt(dist/counter); // usrednianie wartosci
}


std::string SerializeCluster(const Cluster& c) {//! Serializacja danych do zmiennej typu string aby do zapisania wyniku w pliku
	std::string s;

	std::ostringstream st;
	if (!c.getEntity().empty())
	{
		for (auto i : c.getEntity()) { // iteracja przez obiekt clasy Cluster i zapisywanie jego wartosci do strumienia napisowaego
			for (auto  j : i.getLocation()) {
				st <<" " << j << " ";
			}
			st<< std::endl;
		}
	}
	else
	{
		std::cout << "Cannot seralize" << std::endl;
		return "Cannot seralize";
	}
	return st.str(); // konwersja strumienia napisowego na zmiennna typu string
}

std::vector<Cluster> UPGMA(int group_number, std::vector<Cluster>& data) {//! UGMA do grupowania danych
	size_t location_a = 0;
	size_t location_b = 1;
	double x = -1;
	while (data.size() > group_number)
	{
		double min_dist = DBL_MAX;
		for (auto i = data.begin(); i != data.end(); ++i) { // iteracja przez obiekt klasy Cluster w poszukiwaniu dwoch obiektow o najmniejszej odleglosci miedzy soba po czym zlaczenie ich ze soba do jednego obiektu
			for (auto j = data.begin(); j  != data.end(); ++j) {
					x = CalculateDistance(*i, *j); //liczenie odleglosci metoda manhattan a wartosc odleg³osci jest usredniona wartoscia wszystkich odleglosci

					if (x < min_dist&& x!=0) { // zapisanie wartosci oraz polozenia najblizszych klastrow

						location_a = i - data.begin();
						location_b = j - data.begin();
						min_dist = x;
					}
				
			}

		}

		Cluster cg(data.at(location_a), data.at(location_b)); // Wywo³nie konstruktora tworzaczego obiekt klasy Cluster z dwoch innych oobiektow klasy Cluster

		if (location_a > location_b) {// usuwanie obiektow ktore zostaly polaczone oraz dodanie obiektu powstalego z ich polaczenia 
			data.erase(data.begin() + location_a);
			data.erase(data.begin() + location_b);
			data.push_back(cg);
		}
		else {
			data.erase(data.begin() + location_b);
			data.erase(data.begin() + location_a);
			data.push_back(cg);
		}
	}
	return data;
}


