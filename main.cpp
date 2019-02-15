#include <iostream>
#include <string>

class Beverage
{
protected:
	std::string itemname = "";
	std::string brewDetails = "";
	std::string boilWaterDetails = "";
	float itemcost = 0;

public:
	virtual std::string name();
	virtual float cost();
	virtual ~Beverage(){}
	virtual void prepared();
	virtual void brew();
	virtual void boilWater();
	virtual void pour();
	virtual void displayOrder();
};

std::string Beverage::name()
{
	return this->itemname;
}

float Beverage::cost()
{
	return this->itemcost;
}

void Beverage::prepared()
{
	boilWater();
	brew();
	pour();
}

void Beverage::brew()
{
	std::cout << brewDetails << std::endl;
}

void Beverage::boilWater()
{
	std::cout << boilWaterDetails << std::endl;
}

void Beverage::pour()
{
	std::cout << "Pouring..." << std::endl;
}

void Beverage::displayOrder()
{
	std::cout << this->name() << " : Cost: ";
	std::cout << this->cost() << std::endl;
}

class Espresso : public Beverage
{
public:
	Espresso()
	{
		itemname = "Espresso";
		itemcost = 1.2;
		brewDetails = "Filtering Espresso";
		boilWaterDetails = "Heating to 90 Celsius";
	}
};

class Tea : public Beverage
{
	Tea()
	{
		itemname = "Tea";
		itemcost = 1.2;
		brewDetails = "Steeping teabag";
		boilWaterDetails = "Heating to 100 Celsius";
	}
};

class CondimentDecorator : public Beverage
{
protected:
	Beverage* beverage;
	std::string addCondimentDetails = "";
public:
	virtual float cost();
	virtual std::string name();
	virtual void addCondiment();
	void addToBeverage(Beverage* customerBeverage);
	~CondimentDecorator();
	void prepare();
	virtual void brew();
	virtual void boilWater();
	void pour();
};

float CondimentDecorator::cost()
{
	return this->itemcost + beverage->cost();
}

std::string CondimentDecorator::name()
{
	return beverage->name() + " + " + this->itemname;
}

void CondimentDecorator::addCondiment()
{
	std::cout << addCondimentDetails << std::endl;
}

void CondimentDecorator::addToBeverage(Beverage * customerBeverage)
{
	beverage = customerBeverage;
}

CondimentDecorator::~CondimentDecorator()
{
	delete beverage;
}

void CondimentDecorator::prepare()
{
	beverage->prepared();
	addCondiment();
}

void CondimentDecorator::brew()
{
	beverage->brew();
}

void CondimentDecorator::boilWater()
{
	beverage->boilWater();
}

void CondimentDecorator::pour()
{
	beverage->pour();
}

class Mocha : public CondimentDecorator
{
public:
	Mocha()
	{
		itemname = "Mocha";
		itemcost = 0.2;
		addCondimentDetails = "Adding Mocha!";
	}
};

class Cream : public CondimentDecorator
{
public:
	Cream()
	{
		itemname = "Cream";
		itemcost = 0.5;
		addCondimentDetails = "Adding Cream!";
	}
};

int main()
{
	Beverage* currentBeverage = new Tea();

	currentBeverage->displayOrder();

	CondimentDecorator* currentCondiment = new Mocha;
	currentCondiment->addToBeverage(currentBeverage);
	currentBeverage = currentCondiment;
	currentBeverage->displayOrder();
	currentCondiment = new Cream;
	currentCondiment->addToBeverage(currentBeverage);
	currentBeverage = currentCondiment;
	currentBeverage->displayOrder();
	std::cout << '\n';
	currentBeverage->prepared();

	delete currentBeverage;


	return 0;
}
