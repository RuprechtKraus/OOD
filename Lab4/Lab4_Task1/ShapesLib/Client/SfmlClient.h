#pragma once
#include "Canvas/SfmlCanvas.h"
#include "Client.h"
#include "SFML/Graphics.hpp"

class SfmlClient : public Client
{
public:
	SfmlClient();

protected:
	void VisualizeDraft(const PictureDraft& draft, Painter& painter) override;

private:
	sf::RenderWindow m_window;
};