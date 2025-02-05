#include "ShieldTypeClass.h"

Enumerable<ShieldTypeClass>::container_t Enumerable<ShieldTypeClass>::Array;

const char* Enumerable<ShieldTypeClass>::GetMainSection()
{
	return "ShieldTypes";
}

AnimTypeClass* ShieldTypeClass::GetIdleAnimType(bool isDamaged, double healthRatio)
{
	auto damagedAnim = this->IdleAnimDamaged.Get(healthRatio);

	if (isDamaged && damagedAnim)
		return damagedAnim;
	else
		return this->IdleAnim.Get(healthRatio);
}

void ShieldTypeClass::LoadFromINI(CCINIClass* pINI)
{
	const char* pSection = this->Name;
	if (strcmp(pSection, NONE_STR) == 0)
		return;

	INI_EX exINI(pINI);

	this->Strength.Read(exINI, pSection, "Strength");
	this->InitialStrength.Read(exINI, pSection, "InitialStrength");
	this->Armor.Read(exINI, pSection, "Armor");
	this->InheritArmorFromTechno.Read(exINI, pSection, "InheritArmorFromTechno");
	this->Powered.Read(exINI, pSection, "Powered");

	this->Respawn.Read(exINI, pSection, "Respawn");
	Nullable<double> Respawn_Rate__InMinutes;
	Respawn_Rate__InMinutes.Read(exINI, pSection, "Respawn.Rate");
	if (Respawn_Rate__InMinutes.isset())
		this->Respawn_Rate = (int)(Respawn_Rate__InMinutes.Get() * 900);

	this->SelfHealing.Read(exINI, pSection, "SelfHealing");
	Nullable<double> SelfHealing_Rate__InMinutes;
	SelfHealing_Rate__InMinutes.Read(exINI, pSection, "SelfHealing.Rate");
	if (SelfHealing_Rate__InMinutes.isset())
		this->SelfHealing_Rate = (int)(SelfHealing_Rate__InMinutes.Get() * 900);

	this->AbsorbOverDamage.Read(exINI, pSection, "AbsorbOverDamage");
	this->BracketDelta.Read(exINI, pSection, "BracketDelta");

	this->IdleAnim_OfflineAction.Read(exINI, pSection, "IdleAnim.OfflineAction");
	this->IdleAnim_TemporalAction.Read(exINI, pSection, "IdleAnim.TemporalAction");

	this->IdleAnim.Read(exINI, pSection, "IdleAnim.%s");
	this->IdleAnimDamaged.Read(exINI, pSection, "IdleAnimDamaged.%s");

	this->BreakAnim.Read(exINI, pSection, "BreakAnim");
	this->HitAnim.Read(exINI, pSection, "HitAnim");
	this->BreakWeapon.Read(exINI, pSection, "BreakWeapon", true);

	this->AbsorbPercent.Read(exINI, pSection, "AbsorbPercent");
	this->PassPercent.Read(exINI, pSection, "PassPercent");

	this->AllowTransfer.Read(exINI, pSection, "AllowTransfer");

	this->Pips.Read(exINI, pSection, "Pips");
	this->Pips_Background.Read(exINI, pSection, "Pips.Background");
	this->Pips_Building.Read(exINI, pSection, "Pips.Building");
	this->Pips_Building_Empty.Read(exINI, pSection, "Pips.Building.Empty");

	this->ImmuneToBerserk.Read(exINI, pSection, "ImmuneToBerserk");
	this->ImmuneToCrit.Read(exINI, pSection, "ImmuneToCrit");
}

template <typename T>
void ShieldTypeClass::Serialize(T& Stm)
{
	Stm
		.Process(this->Strength)
		.Process(this->InitialStrength)
		.Process(this->Armor)
		.Process(this->InheritArmorFromTechno)
		.Process(this->Powered)
		.Process(this->Respawn)
		.Process(this->Respawn_Rate)
		.Process(this->SelfHealing)
		.Process(this->SelfHealing_Rate)
		.Process(this->AbsorbOverDamage)
		.Process(this->BracketDelta)
		.Process(this->IdleAnim_OfflineAction)
		.Process(this->IdleAnim_TemporalAction)
		.Process(this->IdleAnim)
		.Process(this->BreakAnim)
		.Process(this->HitAnim)
		.Process(this->BreakWeapon)
		.Process(this->AbsorbPercent)
		.Process(this->PassPercent)
		.Process(this->AllowTransfer)
		.Process(this->Pips)
		.Process(this->Pips_Background)
		.Process(this->Pips_Building)
		.Process(this->Pips_Building_Empty)
		.Process(this->ImmuneToBerserk)
		.Process(this->ImmuneToCrit)
		;
}

void ShieldTypeClass::LoadFromStream(PhobosStreamReader& Stm)
{
	this->Serialize(Stm);
}

void ShieldTypeClass::SaveToStream(PhobosStreamWriter& Stm)
{
	this->Serialize(Stm);
}
