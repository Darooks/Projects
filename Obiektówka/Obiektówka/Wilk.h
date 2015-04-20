#pragma once

class Wilk : public Zwierze
{
public:
	Wilk() {	};

	Wilk(int new_x, int new_y, Swiat *tura)
	{
		this->znak = 'W';
		this->sila = 9;
		this->inicjatywa = 5;
		this->polozenie_x = new_x;
		this->polozenie_y = new_y;
		this->rozmnozenie = 0;
		this->wiek = 0;
		this->zwierzak = 0;
		this->smierc = false;
	}

	void rysowanie();
};

void Wilk::rysowanie()
{
	cout << this->znak;
}

//char znak;
//Swiat *tura;
//int sila;
//int inicjatywa;
//int polozenie[20][20];