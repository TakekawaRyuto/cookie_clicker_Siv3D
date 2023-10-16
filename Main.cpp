# include <Siv3D.hpp>

/// @brief アイテムのボタン
/// @param rect ボタンの領域
/// @param texture ボタンの絵文字
/// @param font 文字描画に使うフォント
/// @param name アイテムの名前
/// @param desc アイテムの説明
/// @param count アイテムの所持数
/// @param enabled ボタンを押せるか
/// @return ボタンが押された場合 true, それ以外の場合は false
bool Button(const Rect& rect, const Texture& texture, const Font& font, const String& name, const String& desc, int32 count, bool enabled)
{
	if (enabled)
	{
		rect.draw(ColorF{ 0.3, 0.5, 0.9, 0.8 });

		rect.drawFrame(2, 2, ColorF{ 0.5, 0.7, 1.0 });

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
	else
	{
		rect.draw(ColorF{ 0.0, 0.4 });

		rect.drawFrame(2, 2, ColorF{ 0.5 });
	}

	texture.scaled(0.3).drawAt(rect.x + 50, rect.y + 50);

	font(name).draw(30, rect.x + 100, rect.y + 15, Palette::White);

	font(desc).draw(18, rect.x + 102, rect.y + 60, Palette::White);

	font(count).draw(50, Arg::rightCenter((rect.x + rect.w - 20), (rect.y + 50)), Palette::White);

	return (enabled && rect.leftClicked());
}

void Main()
{
	// クッキーの絵文字
	const Texture akui_img { U"akui.jpg" };

	// 農場の絵文字
	const Texture ark_progrise_key { U"ark_progrise_key.jpg" };

	// 工場の絵文字
	const Texture satellite_ark { U"satellite_ark.jpg" };

	// フォント
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// クッキーのクリック円
	const Circle akuiCircle{ 170, 300, 100 };

	// クッキーの表示サイズ（倍率）
	double akuiScale = 0.75;

	// クッキーの個数
	double akui = 0;
	double perfect_conclusion = 0;
	ColorF akui_Color { 0.7, 0, 0 };

	// 農場の所有数
	int32 Count_ark_progrise_key = 0;

	// 工場の所有数
	int32 Count_satellite_ark = 0;

	// 農場の価格
	int32 Cost_ark_progrise_key = 10;

	// 工場の価格
	int32 Cost_satellite_ark = 100;

	// ゲームの経過時間の蓄積
	double accumulatedTime = 0.0;

	while (System::Update())
	{
		// クッキーの毎秒の生産量 (cookies per second) を計算する
		const int32 cps = (Count_ark_progrise_key + Count_satellite_ark * 10);

		// ゲームの経過時間を加算する
		accumulatedTime += Scene::DeltaTime();

		// 0.1 秒以上蓄積していたら
		if (0.1 <= accumulatedTime)
		{
			accumulatedTime -= 0.1;

			// 0.1 秒分のクッキー生産を加算する
			akui += (cps * 0.1);
		}

		// 農場の価格を計算する
		Cost_ark_progrise_key = 10 + (Count_ark_progrise_key * 10);

		// 工場の価格を計算する
		Cost_satellite_ark = 100 + (Count_satellite_ark * 100);

		// クッキー円上にマウスカーソルがあれば
		if (akuiCircle.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		// クッキー円が左クリックされたら
		if (akuiCircle.leftClicked())
		{
			akuiScale = 0.5;
			++akui;
		}

		// クッキーの表示サイズを回復する
		akuiScale += Scene::DeltaTime();

		if (0.75 < akuiScale)
		{
			akuiScale = 0.75;
		}

		// 背景を描く
		Rect{ 0, 0, 800, 600 }.draw(Arg::top = ColorF{ 0.6, 0, 0 }, Arg::bottom = ColorF{ 0, 0, 0 });

		// クッキーの数を整数で表示する
		font(U"{:.0f}"_fmt(akui)).drawAt(60, 170, 100);

		// クッキーの生産量を表示する
		font(U"毎秒: {}"_fmt(cps)).drawAt(24, 170, 160);

		// クッキーを描画する
		akui_img.scaled(akuiScale).drawAt(akuiCircle.center);

		// 農場ボタン
		if (Button(Rect{ 340, 40, 420, 100 }, ark_progrise_key, font, U"悪意農場", U"C{} / 1 CPS"_fmt(Cost_ark_progrise_key), Count_ark_progrise_key, (Cost_ark_progrise_key <= akui)))
		{
			akui -= Cost_ark_progrise_key;
			++Count_ark_progrise_key;
		}

		// 工場ボタン
		if (Button(Rect{ 340, 160, 420, 100 }, satellite_ark, font, U"悪意工場", U"C{} / 10 CPS"_fmt(Cost_satellite_ark), Count_satellite_ark, (Cost_satellite_ark <= akui)))
		{
			akui -= Cost_satellite_ark;
			++Count_satellite_ark;
		}

		if (50 <= (int32)akui && (int32)akui < 111)
		{
			font(U"悪意").draw(60, 350, 400, akui_Color);
		}
		if (111 <= (int32)akui && (int32)akui < 222)
		{
			font(U"恐怖").draw(60, 340, 400, akui_Color);
		}
		if (222 <= (int32)akui && (int32)akui < 333)
		{
			font(U"憤怒").draw(60, 340, 400, akui_Color);
		}
		if (333 <= (int32)akui && (int32)akui < 444)
		{
			font(U"憎悪").draw(60, 340, 400, akui_Color);
		}
		if (444 <= (int32)akui && (int32)akui < 555)
		{
			font(U"絶望").draw(60, 340, 400, akui_Color);
		}
		if (555 <= (int32)akui && (int32)akui < 666)
		{
			font(U"闘争").draw(60, 340, 400, akui_Color);
		}
		if (666 <= (int32)akui && (int32)akui < 777)
		{
			font(U"殺意").draw(60, 340, 400, akui_Color);
		}
		if (777 <= (int32)akui && (int32)akui < 888)
		{
			font(U"破滅").draw(60, 340, 400, akui_Color);
		}
		if (888 <= (int32)akui && (int32)akui < 999)
		{
			font(U"絶滅").draw(60, 340, 400, akui_Color);
		}
		if (999 <= (int32)akui)
		{
			if (0 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 15)
			{
				font(U"滅亡").draw(60, 340, 400, akui_Color);
				font(U"ラーニングエンド").draw(60, 160, 500, akui_Color);
			}
			if (60 / 5 * 15 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 16)
			{
				font(U"パ").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 16 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 17)
			{
				font(U"ー").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 17 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 18)
			{
				font(U"フ").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 18 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 19)
			{
				font(U"ェ").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 19 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 20)
			{
				font(U"ク").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 20 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 21)
			{
				font(U"ト").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 21 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 22)
			{
				font(U"コ").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 22 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 23)
			{
				font(U"ン").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 23 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 24)
			{
				font(U"ク").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 24 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 25)
			{
				font(U"ル").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 25 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 26)
			{
				font(U"ー").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 26 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 27)
			{
				font(U"ジ").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 27 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 28)
			{
				font(U"ョ").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 28 <= perfect_conclusion && perfect_conclusion < 60 / 5 * 29)
			{
				font(U"ン").draw(300, Arg::center(400, 300), akui_Color);
			}
			if (60 / 5 * 29 <= perfect_conclusion && perfect_conclusion < 60 * 10)
			{
				font(U"パーフェクト").draw(90, 130, 200, akui_Color);
				font(U"コンクルージョン").draw(90, 40, 400, akui_Color);
			}
			if (60 * 10 <= perfect_conclusion)
			{
				System::Exit();
			}
			perfect_conclusion += Scene::DeltaTime() * 60;
		}
	}
}
