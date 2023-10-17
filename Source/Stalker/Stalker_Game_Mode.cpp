#include "Stalker_Game_Mode.h"
#include "StalkerCharacter.h"
#include "UObject/ConstructorHelpers.h"

//------------------------------------------------------------------------------------------------------------
AStalker_Game_Mode::AStalker_Game_Mode()
: Super()
{
	// ��������� ����� ��� pawn �� ��������� � ����� ���������, ������������ � ���������
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
//------------------------------------------------------------------------------------------------------------
