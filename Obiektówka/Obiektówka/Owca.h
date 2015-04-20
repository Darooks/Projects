#pragma once

class Owca : public Zwierze
{
public:
	Owca() {};
	Owca(int new_x, int new_y, Swiat *tura)
	{
		this->znak = 'O';
		this->sila = 4;
		this->inicjatywa = 4;
		this->polozenie_x = new_x;
		this->polozenie_y = new_y;
		this->rozmnozenie = 0;
		this->wiek = 0;
		this->zwierzak = 0;
		this->smierc= false;
	}

	void rysowanie();
};

void Owca::rysowanie()
{
	cout << this->znak;
}