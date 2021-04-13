module;

export module MyModule;

export class MyModuleClass
{
public:
    MyModuleClass() = default;
    int getId() { return id; }
private:
    int id = 10;
};
