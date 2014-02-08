#ifndef ANIMAL_H
#define ANIMAL_H


// abstract base Animal
class Animal {

public:
   virtual void run()const = 0;
   Animal() {}
   virtual ~Animal() {}
};
#endif // ANIMAL_H
