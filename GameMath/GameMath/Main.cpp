#include <Siv3D.hpp>
#include <vector>

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

Vec2 toScene(const Vec2& logical)
{
	const auto center = Scene::Center();
	return { center.x + logical.x, center.y - logical.y };
}

void update();
void draw();

void Main()
{
	while (System::Update())
	{
		update();
		draw();
	}
}

constexpr double moveSpeed = 200.0;
constexpr double playerRadius = 15.0;
Vec2 playerPos{ 0, 0 };

void update()
{
	playerPos.x += (KeyRight.pressed() - KeyLeft.pressed()) * moveSpeed * Scene::DeltaTime();
	playerPos.y += (KeyUp.pressed() - KeyDown.pressed()) * moveSpeed * Scene::DeltaTime();
}

void draw()
{
	RenderGrid();

	float rad = 0.f;
	
	std::vector<Circle> hearts;
	
	if (hearts.empty())
	{
		for (rad = 0.f; rad < Math::TwoPi; rad += 0.01f)
		{
			float sin = sinf(rad);
			float cos = cosf(rad);
			float cos2 = cosf(rad * 2);
			float cos3 = cosf(rad * 3);
			float cos4 = cosf(rad * 4);
			float x = 16.f * sin * sin * sin;
			float y = 13 * cos - 5 * cos2 - 2 * cos3 - cos4;
			hearts.push_back(Circle { x, y , 1 });
		}
	}
	
	for (auto& c : hearts)
	{
		c.center = toScene(c.center * 10 + playerPos);
		c.draw();
	}
}
