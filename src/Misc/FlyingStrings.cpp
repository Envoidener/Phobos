#include "FlyingStrings.h"

#include <MapClass.h>
#include <Phobos.CRT.h>
#include <TacticalClass.h>
#include <ColorScheme.h>
#include <Drawing.h>
#include <ScenarioClass.h>
#include <BitFont.h>
#include <Utilities/EnumFunctions.h>

std::vector<FlyingStrings::Item> FlyingStrings::Data;

bool FlyingStrings::DrawAllowed(CoordStruct& nCoords)
{
	if (auto const pCell = MapClass::Instance->TryGetCellAt(nCoords))
		return !(pCell->IsFogged() || pCell->IsShrouded());

	return false;
}

void FlyingStrings::Add(const wchar_t* text, CoordStruct coords, ColorStruct color, Point2D pixelOffset)
{
	Item item {};
	item.Location = coords;
	item.PixelOffset = pixelOffset;
	item.CreationFrame = Unsorted::CurrentFrame;
	item.Color = Drawing::RGB_To_Int(color);
	PhobosCRT::wstrCopy(item.Text, text, 0x20);
	Data.push_back(item);
}

void FlyingStrings::AddNumberString(int amount, HouseClass* owner, AffectedHouse displayToHouses,
	ColorStruct color, CoordStruct coords, Point2D pixelOffset, bool sign, const wchar_t* prefix)
{
	if (displayToHouses == AffectedHouse::All ||
		owner && EnumFunctions::CanTargetHouse(displayToHouses, owner, HouseClass::CurrentPlayer))
	{
		bool isPositive = amount > 0;
		const wchar_t* sign_symbol = (sign && amount != 0) ? (isPositive ? L"+" :  L"-") : L"";
		wchar_t displayStr[0x20];
		swprintf_s(displayStr, L"%ls%ls%d", sign_symbol, prefix, std::abs(amount));

		int width = 0, height = 0;
		BitFont::Instance->GetTextDimension(displayStr, &width, &height, 120);
		pixelOffset.X -= (width / 2);

		FlyingStrings::Add(displayStr, coords, color, pixelOffset);
	}
}

void FlyingStrings::UpdateAll()
{
	if (Data.empty())
		return;

	for (int i = Data.size() - 1; i >= 0; --i)
	{
		auto& dataItem = Data[i];

		Point2D point;

		TacticalClass::Instance->CoordsToClient(dataItem.Location, &point);

		point += dataItem.PixelOffset;

		RectangleStruct bound = DSurface::Temp->GetRect();
		bound.Height -= 32;

		if (Unsorted::CurrentFrame > dataItem.CreationFrame + Duration - 70)
		{
			point.Y -= (Unsorted::CurrentFrame - dataItem.CreationFrame);
			DSurface::Temp->DrawText(dataItem.Text, &bound, &point, dataItem.Color, 0, TextPrintType::NoShadow);
		}
		else
		{
			DSurface::Temp->DrawText(dataItem.Text, &bound, &point, dataItem.Color, 0, TextPrintType::NoShadow);
		}

		if (Unsorted::CurrentFrame > dataItem.CreationFrame + Duration || Unsorted::CurrentFrame < dataItem.CreationFrame)
			Data.erase(Data.begin() + i);
	}
}
