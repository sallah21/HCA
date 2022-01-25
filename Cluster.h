#pragma once
#include <vector>
#include "Entity.h"
#include<iostream>
#include<sstream>

	class Cluster
	{
		std::vector<Entity<double>> data; //! wektor przechowywuj¹cy pojedyncze encje ktore beda grupowane
		size_t  length;
	public:
		std::vector<Entity<double>> getEntity()const { return this->data; } //! sprawdzanie zawartosci klastra 
		size_t getEntitySize()const { return this->length; } //! sprawdzanie dlugosci klasytra
		Cluster(Cluster& c1, Cluster& c2);//! konstruktor sumujacy zawartosci dwoch roznych klastrow do jednego nowego 




		Cluster(const Entity<double> e) { //! tworzenie klastra z pojedynczej klasy Entity
			std::vector<Entity<double>> v;
			v.push_back(e);
			this->data = v;
			this->length = 1;
		}
		Cluster(std::vector<double>& v) { //! tworzenie klastra z pojedynczego wektora danych (konstrukcja posrednia wektora klasy Entity)

			Entity<double> e(v);
			std::vector<Entity<double>> ve;
			ve.push_back(e);
			this->data = ve;
			this->length = 1;
		}
		~Cluster() {
			this->data.~vector();
		}

	};

	std::vector<Cluster> UPGMA(int k, std::vector<Cluster>& data);
	double CalculateDistance(const Cluster& c1, const Cluster& c2); //! kalkulacja odleglosci miedzy klastrami
	std::string SerializeCluster(const Cluster& c); //! serializacja danych z klastra do zmiennej typu string
