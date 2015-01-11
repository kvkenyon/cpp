#include <iostream>
#include <cassert>

using namespace std;

class WeaponBehavior {
public:
	virtual void use_weapon();
};

void WeaponBehavior::use_weapon() {
	cout << "Fist attack." << endl;
}

class AxeBehavior : public WeaponBehavior {
public:	
	virtual void use_weapon() {
		cout << "Axe attack." << endl;
	}
};

class KnifeBehavior : public WeaponBehavior {
public:
	void use_weapon() {
		cout << "Knife attack." << endl;
	}
};

class SwordBehavior : public WeaponBehavior {
public:
	void use_weapon() {
		cout << "Sword attack." << endl;
	}
};

class Character {

private:
	WeaponBehavior _wb;

public:
	Character(const WeaponBehavior& wb) : _wb(wb)
		{}

	void fight() {
		_wb.use_weapon();}
};

class Queen : public Character {

public:
	Queen(KnifeBehavior kb) : Character(kb)
		{}
};

class King : public Character {
public:
	King(AxeBehavior ab) : Character(ab)
		{}
};

int main() {
	using namespace std;

	{
		AxeBehavior axe;
		King kublai_khan(axe);
		kublai_khan.fight();
	}

}