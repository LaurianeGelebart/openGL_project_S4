#include "p6/p6.h"
#include "GameEnvironment.hpp"

void GameEnvironment::initScene()
{
    initObjectModel();
    initBoids();
    initObstacles();
    initClouds();
    initArpenteur();
    initContent();
}

void GameEnvironment::deleteScene()
{
    for(auto& obstacle : this->obstacles){
        obstacle.deleteVAO_VBO() ; 
    }
    for(auto& boid : this->boids){
        boid.deleteVAO_VBO() ; 
    }
    for(auto& cloud : this->clouds){
        cloud.deleteVAO_VBO() ; 
    }
    gaspard[0].deleteVAO_VBO() ; 
    box[0].deleteVAO_VBO() ; 
    glfwTerminate();
}


void GameEnvironment::initObjectModel()
{
    this->_puit = Loader("./assets/models/puit.obj", materialMap, nb_slot);
    this->_magic = Loader("./assets/models/magique.obj", materialMap, nb_slot);
    this->_content = Loader("./assets/models/content.obj", materialMap, nb_slot);
    this->_fir1 = Loader("./assets/models/fir1.obj", materialMap, nb_slot);
    this->_fir2 = Loader("./assets/models/fir2.obj", materialMap, nb_slot);
    this->_fir3 = Loader("./assets/models/fir3.obj", materialMap, nb_slot);
    this->_mushroom1 = Loader("./assets/models/mushroom1.obj", materialMap, nb_slot);
    this->_mushroom2 = Loader("./assets/models/mushroom2.obj", materialMap, nb_slot);
    this->_rock1 = Loader("./assets/models/rock1.obj", materialMap, nb_slot);
    this->_rock2 = Loader("./assets/models/rock2.obj", materialMap, nb_slot);
    this->_rock3 = Loader("./assets/models/rock3.obj", materialMap, nb_slot);
    this->_house = Loader("./assets/models/house.obj", materialMap, nb_slot);
    this->_rocks = Loader("./assets/models/rocks.obj", materialMap, nb_slot);
    this->_rail = Loader("./assets/models/rail.obj", materialMap, nb_slot);
    this->_barel = Loader("./assets/models/barel.obj", materialMap, nb_slot);
    this->_cloud = Loader("./assets/models/cloud1.obj", materialMap, nb_slot);
    this->_panneau = Loader("./assets/models/panneau.obj", materialMap, nb_slot);
    this->_sphere = Loader("./assets/models/sphere.obj", materialMap, nb_slot);

 
}

void GameEnvironment::initBoids()
{
    for(int i=0 ; i<this->_ihm.get_nb_boids() ; i++){
         Boid b(this->_sphere, this->_textureProgram, this->_magicPos) ;
         this->boids.push_back(b);
    }
}

void GameEnvironment::initObstacles()
{
    this->obstacles.push_back(Obstacle(this->_house, this->_textureProgram, Vec(-4.0, 0.0, 0.0))) ;
    this->obstacles.push_back(Obstacle(this->_puit, this->_textureProgram, Vec(3.0, 0.0, 4.0))) ;
    this->obstacles.push_back(Obstacle(this->_rail, this->_textureProgram, Vec(-18.0, 0.0, 18.0))) ;
    this->obstacles.push_back(Obstacle(this->_rocks, this->_textureProgram, Vec(-4.0, 0.0, 4.0))) ;
    this->obstacles.push_back(Obstacle(this->_barel, this->_textureProgram, Vec(-4.0, 0.0, 0.0))) ;
    this->obstacles.push_back(Obstacle(this->_magic, this->_textureProgram, this->_magicPos)) ;
    this->obstacles.push_back(Obstacle(this->_panneau, this->_textureProgram, Vec(-10.0, 0.0, 13.0))) ;

    for(int i=6; i < this->_ihm.get_nb_obstacles(); i++){
        float j = p6::random::number(); 
        if(j < 0.2) {
            this->obstacles.push_back(Obstacle(this->_fir1, this->_textureProgram));
        } else if(j < 0.4) {
            this->obstacles.push_back(Obstacle(this->_fir2, this->_textureProgram));
        } else if (j < 0.6){
            this->obstacles.push_back(Obstacle(this->_fir3, this->_textureProgram));
        } else if(j < 0.65) {
            this->obstacles.push_back(Obstacle(this->_mushroom1, this->_textureProgram));
        } else if (j < 0.7){
            this->obstacles.push_back(Obstacle(this->_mushroom2, this->_textureProgram));
        }else if (j < 0.8){
            this->obstacles.push_back(Obstacle(this->_rock1, this->_textureProgram));
        } else if(j < 0.9) {
            this->obstacles.push_back(Obstacle(this->_rock2, this->_textureProgram));
        } else {
            this->obstacles.push_back(Obstacle(this->_rock3, this->_textureProgram));
        }
    }

  }

void GameEnvironment::initClouds()
{
    for(int i=0 ; i<3 ; i++){
         Cloud c(this->_cloud, this->_textureProgram) ;
         this->clouds.push_back(c);
     }    
}

void GameEnvironment::initArpenteur()
{
    this->gaspard.push_back(Arpenteur(this->_barel, this->_textureProgram)) ; 
}

void GameEnvironment::initContent()
{
    this->box.push_back(Content(this->_content, this->_textureProgram)) ;
}

void GameEnvironment::render(p6::Context &ctx)
{
    for(auto& boid : this->boids){
        boid.draw(this->_ViewMatrix, window_width, window_height, this->materialMap) ;
        boid.collision(this->boids, this->obstacles, this->_ihm, ctx) ;
        boid.update_position() ;
    };

    for(auto& obstacle : this->obstacles){
        obstacle.draw(this->_ViewMatrix, window_width, window_height, this->materialMap) ;
    };

    for(auto& cloud : this->clouds){
        cloud.draw(this->_ViewMatrix, window_width, window_height, this->materialMap) ;
        cloud.update_position(ctx) ;
    }

    this->box[0].draw(this->_ViewMatrix, window_width, window_height, this->materialMap) ;
     this->gaspard[0].draw(this->_ViewMatrix, window_width, window_height, this->materialMap) ;
    this->gaspard[0].update_position(this->_ViewMatrix); 

    this->_ihm.draw();

    add_or_remove_boids() ;
    add_or_remove_obstacles() ;

}

void GameEnvironment::cameraManagement(p6::Context &ctx){
    if (_Z) this->_ViewMatrix.moveFront(0.1);
    if (_S) this->_ViewMatrix.moveFront(-0.1);
    if (_Q) this->_ViewMatrix.moveLeft(0.1);
    if (_D) this->_ViewMatrix.moveLeft(-0.1);

    ctx.key_pressed = [this](const p6::Key& key) {
        if (key.physical == GLFW_KEY_W) this->_Z = true;
        if (key.physical == GLFW_KEY_S) this->_S = true;
        if (key.physical == GLFW_KEY_A) this->_Q = true;
        if (key.physical == GLFW_KEY_D) this->_D = true;
    };

    ctx.key_released = [this](const p6::Key& key) {
        if (key.physical == GLFW_KEY_W) this->_Z = false;
        if (key.physical == GLFW_KEY_S) this->_S = false;
        if (key.physical == GLFW_KEY_A) this->_Q = false;
        if (key.physical == GLFW_KEY_D) this->_D = false;
    };

    glfwSetInputMode(ctx.underlying_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    ctx.mouse_moved = [&](p6::MouseMove data) {
        (this->_ViewMatrix).rotateLeft(data.delta.x * rotationStrength);
        (this->_ViewMatrix).rotateUp(-data.delta.y * rotationStrength);
    };
}


void GameEnvironment::add_or_remove_boids()
{
    int nb_boids = this->boids.size();

    if (nb_boids < this->_ihm.get_nb_boids()){
        for(int i=0 ; i< this->_ihm.get_nb_boids()-nb_boids ; i++){
            Boid b(this->_sphere, this->_textureProgram, this->_magicPos) ;
            this->boids.push_back(b);
        }
    }
    else if (nb_boids > this->_ihm.get_nb_boids()){
        for(int i=0 ; i< nb_boids-this->_ihm.get_nb_boids() ; i++){
            this->boids.pop_back();
        }
    }
}

void GameEnvironment::add_or_remove_obstacles()
{
    int nb_obstacles = obstacles.size();

    if (nb_obstacles < this->_ihm.get_nb_obstacles()){
        for(int i=0 ; i< this->_ihm.get_nb_obstacles() ; i++){
            Obstacle o(this->_fir1, this->_textureProgram) ;
            obstacles.push_back(o);
        }
    }
    else if (nb_obstacles > this->_ihm.get_nb_obstacles()){
        for(int i=0 ; i< nb_obstacles-this->_ihm.get_nb_obstacles() ; i++){
            obstacles.pop_back();
        }
    }
}