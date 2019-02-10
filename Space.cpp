#include "Main.hpp"
using namespace std;

Space::Space(GLfloat xIn, GLfloat yIn, GLTexture srcTextures) : RendObj(xIn, yIn, srcTextures), up(nullptr), down(nullptr), left(nullptr), right(nullptr), dist(-1), isNode{false}, arcs{vector<Arc*>{}}
{
    textures.x = 0;
    textures.y = 0;
}
void Space::neighbours(Level* thisLevel)
{
	for(unsigned int i = 0; i < thisLevel->spaces.size(); i++)
	{
		if((thisLevel->spaces[i]->x == x) and (thisLevel->spaces[i]->y == (y + 32))) {down = thisLevel->spaces[i];}
		if((thisLevel->spaces[i]->x == x) and (thisLevel->spaces[i]->y == (y - 32))) {up = thisLevel->spaces[i];}
		if((thisLevel->spaces[i]->y == y) and (thisLevel->spaces[i]->x == (x + 32))) {right = thisLevel->spaces[i];}
		if((thisLevel->spaces[i]->y == y) and (thisLevel->spaces[i]->x == (x - 32))) {left = thisLevel->spaces[i];}
	}
}
void Space::continueArc(Arc* arc)
{
    vector<Space*> neighbours{vector<Space*>{}};
    if(up != nullptr) {neighbours.push_back(up);}
    if(down != nullptr) {neighbours.push_back(down);}
    if(left != nullptr) {neighbours.push_back(left);}
    if(right != nullptr) {neighbours.push_back(right);}
    arc->add(this);
    arcs.push_back(arc);
    if(neighbours.size() <= 2)
    {
        isNode = false;
        //cerr << "CONTI: " << x / 32 << " "  << y  / 32 << " / " << neighbours.size() << endl;
        if(neighbours.size() > 0 and neighbours[0]->isNode)
        {
            neighbours[0]->continueArc(arc);
        }
        if(neighbours.size() > 1 and neighbours[1]->isNode)
        {
            neighbours[1]->continueArc(arc);
        }
    }
    else
    {
        //cerr << "ENDIN: " << x / 32 << " "  << y  / 32 << endl;
    }
}
int Space::nodeEvaluation(Space* target)
{
    return dist + abs(x - target->x) + abs(y - target->y);
}
void Space::added_to_permanent()
{
    //cerr << "ADD: " << arcs.size() << endl;
    for(auto it: arcs)
    {
        it->recomputeDistance(dist, this);
    }
}
