#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

double getPt(const double& n1, const double& n2, const double& perc) {
	return n1 + ((n2 - n1) * perc);
}

struct Curve {
	vector<vector<Vertex>> vertices;
	int NumberOfVertices = 0;
};

int main()
{
	Vector2i mousePos;
	vector<Curve> curves(1);
	vector<Vertex> points2;
	RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	Event event;

	while (window.isOpen())
	{
		window.clear();

		while (window.pollEvent(event)) {
			mousePos = Mouse::getPosition(window);

			if (event.type == Event::Closed) window.close();

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
				curves[curves.size() - 1].NumberOfVertices++;
				curves[curves.size() - 1].vertices.clear();

				Vertex tempPoint;
				tempPoint.position.x = mousePos.x;
				tempPoint.position.y = mousePos.y;

				points2.push_back(tempPoint);
				curves[curves.size() - 1].vertices.push_back(points2);
				for (int i = curves[curves.size() - 1].NumberOfVertices - 1; i > 0; --i) {
					vector<Vertex> temp;
					for (int j = i; j > 0; --j) {
						Vertex emptyVertex;
						temp.push_back(emptyVertex);
					}
					curves[curves.size() - 1].vertices.push_back(temp);
				}
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Right) {
				Curve newCurve;
				points2.clear();
				points2.push_back(curves[curves.size() - 1].vertices[0][curves[curves.size() - 1].NumberOfVertices - 1]);
				newCurve.vertices.push_back(points2);
				newCurve.NumberOfVertices++;
				curves.push_back(newCurve);
			}
		}

		for (auto& curve : curves) {
			if (curve.NumberOfVertices > 0) {
				for (double i = 0; i <= 1.; i += 0.0001) {
					for (int j = 0; j < curve.vertices.size() - 1; ++j) {
						for (int k = 0; k < curve.vertices[j].size() - 1; ++k) {
							curve.vertices[j + 1][k].position.x = getPt(curve.vertices[j][k].position.x, curve.vertices[j][k + 1].position.x, i);
							curve.vertices[j + 1][k].position.y = getPt(curve.vertices[j][k].position.y, curve.vertices[j][k + 1].position.y, i);
						}
					}
					window.draw(&curve.vertices[curve.vertices.size() - 1][0], 1, Points);
				}
			}
		}

		window.display();
	}

	return 0;
}