# include <Siv3D.hpp>

const double unitSize = 20.0;

void RenderGrid()
{
	const auto center = Scene::Center(); 
	const auto sceneSize = Scene::Size();

	for (double x = 0; x < sceneSize.x; x += unitSize) {
		double relativeX = (x - center.x);
		Color color = (Abs(relativeX) < 0.1) ? Palette::Green : Color(80);
		Line{ x, 0, x, sceneSize.y }.draw(1, color);
	}

	for (double y = 0; y < sceneSize.y; y += unitSize) {
		double relativeY = (y - center.y);
		Color color = (Abs(relativeY) < 0.1) ? Palette::Red : Color(80);
		Line{ 0, y, sceneSize.x, y }.draw(1, color);
	}
}

void update();
void draw();

void Main()
{
	while (System::Update())
	{
		RenderGrid();
		update();
		draw();
	}
}

const int moveSpeed = 100.f;

void update()
{
	KeyA.down();
}

void render()
{

}
