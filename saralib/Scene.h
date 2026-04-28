//Basic container for everything

//extends shape class

/*
    List of objects
    constructor with the objects
    and light

    way to clear obj list
    way to add obj
    intersect 
    color
    computeraycolor
    shadowChecker

    store:
    list of shapes
    list of lights
    list of shaders
    list of cameras
    background color
*/

class Scene{
    public:
        Scene() {}

    private:
        std::vector<std::shared_ptr<Shape>> shapes;
        std::vector<std::shared_ptr<PointLight>> lights;
        vec3 backgroundColor;
}