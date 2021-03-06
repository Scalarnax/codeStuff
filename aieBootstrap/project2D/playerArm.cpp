#include "playerArm.h"
#include "Input.h"
#include "entity.h"
#include "vector2.h"
#include "Matrix3.h"

using namespace aie;

//constructor setting the parent
playerArm::playerArm()
{
	m_armT = new Texture("./textures/arm.png");
	bulet = new bullet;
	bulet->setPerent(this);
	setChild(bulet);
}

//destructor deleting things as it does
playerArm::~playerArm()
{
	delete m_armT;
	delete bulet;
}

//update funbction
void playerArm::update(float deltaTime)
{
	Vector2 Target;

	Vector2 pos;
	Input* input = Input::getInstance();

	Renderer2D m_2dRender;

	Target.x = input->getMouseX();
	Target.y = input->getMouseY();

	Target.x = Target.x + (m_globalTransform[2][0] - 750);
	Target.y = Target.y + (m_globalTransform[2][1] - 500);

	pos = getPos();

	Vector2 lookAt = Target - pos;
	lookAt.normalise();

	m_localTransform[1][0] = lookAt.x;
	m_localTransform[1][1] = lookAt.y;

	m_localTransform[0][0] = lookAt.y;
	m_localTransform[0][1] = -lookAt.x;


	if (input->isMouseButtonDown(INPUT_MOUSE_BUTTON_LEFT))
	{
		bulet->shoot(lookAt, pos);
	}
	bulet->update(deltaTime);

}

//draw function
void playerArm::draw(aie::Renderer2D* m_2dRender)
{
	m_2dRender->drawSpriteTransformed3x3(m_armT, m_globalTransform, 0, 0, 0, 0.3, 0.3);
	bulet->draw(m_2dRender);
}