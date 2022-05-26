#pragma once
#include "main.h"

namespace std {
	class vector3 {
	public:
		std::float_t x{};
		std::float_t y{};
		std::float_t z{};
	};
}

class Vector3 {
public:
	std::float_t x{};
private:
	std::uint8_t x_pad[4]{};
public:
	std::float_t y{};
private:
	std::uint8_t y_pad[4]{};
public:
	std::float_t z{};
private:
	std::uint8_t z_pad[4]{};
};

class Vector2 {
public:
	std::float_t x{};
	std::float_t y{};
};

class WaterQuad
{
public:
	std::int16_t minX; //0x0000
	std::int16_t minY; //0x0002
	std::int16_t maxX; //0x0004
	std::int16_t maxY; //0x0006
	std::int8_t a1; //0x0008
	std::int8_t a2; //0x0009
	std::int8_t a3; //0x000A
	std::int8_t a4; //0x000B
	std::float_t unk; //0x000C
	std::uint8_t pad_0010[4]; //0x0010
	std::float_t z; //0x0014
	std::uint8_t pad_0018[1]; //0x0018
	std::int8_t Type; //0x0019
	std::uint8_t pad_001A[2]; //0x001A
}; //Size: 0x001C

class CGameScriptId
{
public:
	uint32_t ScriptHash; //0x0008
	char ScriptName[32]; //0x000C
	char pad_002C[4]; //0x002C
	uint32_t Timestamp; //0x0030
	uint32_t ScriptId; //0x0034
	uint32_t InstanceId; //0x0038
	uint32_t InstanceHash; //0x003C
	char pad_0040[16]; //0x0040

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
}; //Size: 0x0050

class CGameScriptHandlerNetComponent
{
public:
	class CGameScriptHandlerNetwork* GameScriptHandlerNetwork; //0x0008
	char pad_0010[408]; //0x0010

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void MigrateHostToPlayer(std::uint64_t); // net game player // TODO
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
}; //Size: 0x01A8

class CGameScriptHandlerNetwork
{
public:
	char pad_0008[16]; //0x0008
	class GtaThreadV2* Thread; //0x0018
	char pad_0020[40]; //0x0020
	class CGameScriptHandlerNetComponent* GameScriptHandlerNetComponent; //0x0048
	char pad_0050[16]; //0x0050
	class CGameScriptId GameScriptId; //0x0060

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
}; //Size: 0x00B0

class GtaThreadV2
{
public:
	uint32_t ThreadId; //0x0008
	uint32_t ThreadHash; //0x000C
	uint32_t ThreadState; //0x0010
	uint32_t ProgramCounter; //0x0014
	uint32_t StackFramePointer; //0x0018
	uint32_t StackPointer; //0x001C
	uint32_t TimerA; //0x0020
	uint32_t TimerB; //0x0024
	float WaitTime; //0x0028
	char pad_002C[156]; //0x002C
	char* Message; //0x00C8
	char ScriptName[64]; //0x00D0
	class CGameScriptHandlerNetwork* GameScriptHandlerNetwork; //0x0110
	class CGameScriptHandlerNetComponent* GameScriptHandlerNetComponent; //0x0118
	uint32_t ScriptHash; //0x0120
	char pad_0124[76]; //0x0124

	virtual void SharedCtor(); // idk what to call this but eh makes sense
	virtual void Reset();
	virtual void Tick();
	virtual void Sleep();
	virtual void Kill();
}; //Size: 0x0170

class CAmmoInfo
{
public:
	char pad_0008[8]; //0x0008
	std::uint32_t AmmoHash; //0x0010
	std::uint32_t Name; //0x0014
	std::uint32_t Model; //0x0018
	std::uint32_t Slot; //0x001C
	std::int32_t AmmoMax; //0x0020
	std::int32_t AmmoMax50; //0x0024
	std::int32_t AmmoMax100; //0x0028
	std::int32_t AmmoMaxMP; //0x002C
	std::int32_t AmmoMax50MP; //0x0030
	std::int32_t AmmoMax100MP; //0x0034
	std::uint64_t AmmoFlags; //0x0038

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
}; //Size: 0x0040

class CBuilding
{
public:
	std::uint64_t vmt; //0x0000
	char pad_0008[24]; //0x0008
	std::uint64_t model_info; //0x0020
	char pad_0028[56]; //0x0028
	float s1; //0x0060
	char pad_0064[16]; //0x0064
	float s2; //0x0074
	char pad_0078[4]; //0x0078
	float s3; //0x007C
	char pad_0080[8]; //0x0080
	float s4; //0x0088
	float s5; //0x008C
	float x; //0x0090
	float y; //0x0094
	float z; //0x0098
	char pad_009C[52]; //0x009C
}; //Size: 0x00D0

class CAimingInfo
{
public:
	std::uint32_t Name; //0x0000
	std::float_t HeadingLimit; //0x0004
	std::float_t SweepPitchMin; //0x0008
	std::float_t SweepPitchMax; //0x000C
}; //Size: 0x0010

class COverrideForceInfo
{
public:
	std::int32_t BoneTag; //0x0000
	std::float_t ForceFront; //0x0004
	std::float_t ForceBack; //0x0008
}; //Size: 0x000C

class CWeaponInfo
{
public:
	char pad_0008[8]; //0x0008
	std::uint32_t Name; //0x0010
	std::uint32_t Model; //0x0014
	std::uint32_t Audio; //0x0018
	std::uint32_t Slot; //0x001C
	std::int32_t DamageType; //0x0020
	std::uint32_t Explosion_Default; //0x0024
	std::uint32_t Explosion_HitCar; //0x0028
	std::uint32_t Explosion_HitTruck; //0x002C
	std::uint32_t Explosion_HitBike; //0x0030
	std::uint32_t Explosion_HitBoat; //0x0034
	std::uint32_t Explosion_HitPlane; //0x0038
	char pad_003C[24]; //0x003C
	std::int32_t FireType; //0x0054
	std::int32_t WheelSlot; //0x0058
	std::uint32_t GroupHash; //0x005C
	class CAmmoInfo* AmmoInfo; //0x0060
	class CAimingInfo* AimingInfo; //0x0068
	std::int32_t ClipSize; //0x0070
	std::float_t AccuracySpread; //0x0074
	std::float_t AccurateModeAccuracyModifier; //0x0078
	std::float_t RunAndGunAccuracyModifier; //0x007C
	std::float_t RunAndGunAccuracyMinOverride; //0x0080
	std::float_t RecoilAccuracyMax; //0x0084
	std::float_t RecoilErrorTime; //0x0088
	std::float_t RecoilRecoveryRate; //0x008C
	std::float_t RecoilAccuracyToAllowHeadShotAI; //0x0090
	std::float_t MinHeadShotDistanceAI; //0x0094
	std::float_t MaxHeadShotDistanceAI; //0x0098
	std::float_t HeadShotDamageModifierAI; //0x009C
	std::float_t RecoilAccuracyToAllowHeadShotPlayer; //0x00A0
	std::float_t MinHeadShotDistancePlayer; //0x00A4
	std::float_t MaxHeadShotDistancePlayer; //0x00A8
	std::float_t HeadShotDamageModifierPlayer; //0x00AC
	std::float_t Damage; //0x00B0
	std::float_t DamageTime; //0x00B4
	std::float_t DamageTimeInVehicle; //0x00B8
	std::float_t DamageTimeInVehicleHeadShot; //0x00BC
	std::float_t HitLimbsDamageModifier; //0x00C0
	std::float_t NetworkHitLimbsDamageModifier; //0x00C4
	std::float_t LightlyArmouredDamageModifier; //0x00C8
	std::float_t VehicleDamageModifier; //0x00CC
	std::float_t Force; //0x00D0
	std::float_t ForceHitPed; //0x00D4
	std::float_t ForceHitVehicle; //0x00D8
	std::float_t ForceHitFlyingHeli; //0x00DC
	class COverrideForceInfo* OverrideForceInfo; //0x00E0
	std::int16_t OverrideForceInfoAmount; //0x00E8
	std::int16_t OverrideForceInfoCount; //0x00EA
	char pad_00EC[4]; //0x00EC
	std::float_t ForceMaxStrengthMult; //0x00F0
	std::float_t ForceFalloffRangeStart; //0x00F4
	std::float_t ForceFalloffRangeEnd; //0x00F8
	std::float_t ForceFalloffMin; //0x00FC
	std::float_t ProjectileForce; //0x0100
	std::float_t FragImpulse; //0x0104
	std::float_t Penetration; //0x0108
	std::float_t VerticalLaunchAdjustment; //0x010C
	std::float_t DropForwardVelocity; //0x0110
	std::float_t Speed; //0x0114
	std::int32_t BulletsInBatch; //0x0118
	std::float_t BatchSpread; //0x011C
	std::float_t ReloadTimeMP; //0x0120
	std::float_t ReloadTimeSP; //0x0124
	std::float_t VehicleReloadTime; //0x0128
	std::float_t AnimReloadRate; //0x012C
	std::int32_t BulletsPerAnimLoop; //0x0130
	std::float_t TimeBetweenShots; //0x0134
	std::float_t TimeLeftBetweenShotsWhereShouldFireIsCached; //0x0138
	std::float_t SpinUpTime; //0x013C
	std::float_t SpinTime; //0x0140
	std::float_t SpinDownTime; //0x0144
	std::float_t AlternateWaitTime; //0x0148
	std::float_t BulletBendingNearRadius; //0x014C
	std::float_t BulletBendingFarRadius; //0x0150
	std::float_t BulletBendingZoomedRadius; //0x0154
	std::float_t FirstPersonBulletBendingNearRadius; //0x0158
	std::float_t FirstPersonBulletBendingFarRadius; //0x015C
	std::float_t FirstPersonBulletBendingZoomedRadius; //0x0160
	char pad_0164[12]; //0x0164
	std::int32_t EffectGroup; //0x0170
	std::uint32_t FlashFx; //0x0174
	std::uint32_t FlashFxAlt; //0x0178
	std::uint32_t FlashFxFP; //0x017C
	std::uint32_t FlashFxFPAlt; //0x0180
	std::uint32_t MuzzleSmokeFx; //0x0184
	std::uint32_t MuzzleSmokeFxFP; //0x0188
	char pad_018C[20]; //0x018C
	std::vector3 MuzzleOverrideOffset; //0x01A0
	char pad_01AC[8]; //0x01AC
	std::uint32_t ShellFx; //0x01B4
	std::uint32_t ShellFxFP; //0x01B8
	std::uint32_t TracerFx; //0x01BC
	std::uint32_t PedDamageHash; //0x01C0
	std::float_t TracerFxChanceSP; //0x01C4
	std::float_t TracerFxChanceMP; //0x01C8
	char pad_01CC[4]; //0x01CC
	std::float_t FlashFxChanceSP; //0x01D0
	std::float_t FlashFxChanceMP; //0x01D4
	std::float_t FlashFxAltChance; //0x01D8
	std::float_t FlashFxScale; //0x01DC
	char pad_01E0[4]; //0x01E0
	std::float_t FlashFxLightOffsetDist; //0x01E4
	char pad_01E8[80]; //0x01E8
	std::float_t GroundDisturbFxDist; //0x0238
	std::uint32_t GroundDisturbFxNameDefault; //0x023C
	std::uint32_t GroundDisturbFxNameSand; //0x0240
	std::uint32_t GroundDisturbFxNameDirt; //0x0244
	std::uint32_t GroundDisturbFxNameWater; //0x0248
	std::uint32_t GroundDisturbFxNameFoliage; //0x024C
	std::int32_t InitialRumbleDuration; //0x0250
	std::float_t InitialRumbleIntensity; //0x0254
	std::float_t InitialRumbleIntensityTrigger; //0x0258
	std::int32_t RumbleDuration; //0x025C
	std::float_t RumbleIntensity; //0x0260
	std::float_t RumbleIntensityTrigger; //0x0264
	std::float_t RumbleDamageIntensity; //0x0268
	std::int32_t InitialRumbleDurationFps; //0x026C
	std::float_t InitialRumbleIntensityFps; //0x0270
	std::int32_t RumbleDurationFps; //0x0274
	std::float_t RumbleIntensityFps; //0x0278
	std::float_t NetworkPlayerDamageModifier; //0x027C
	std::float_t NetworkPedDamageModifier; //0x0280
	std::float_t NetworkHeadShotPlayerDamageModifier; //0x0284
	std::float_t LockOnRange; //0x0288
	std::float_t WeaponRange; //0x028C
	std::float_t AiSoundRange; //0x0290
	std::float_t AiPotentialBlastEventRange; //0x0294
	std::float_t DamageFallOffRangeMin; //0x0298
	std::float_t DamageFallOffRangeMax; //0x029C
	char pad_02A0[4]; //0x02A0
	std::float_t DamageFallOffModifier; //0x02A4
	char pad_02A8[4]; //0x02A8
	std::uint32_t DefaultCameraHash; //0x02AC
	std::uint32_t AimCameraHash; //0x02B0
	std::uint32_t FireCameraHash; //0x02B4
	std::uint32_t CoverCameraHash; //0x02B8
	std::uint32_t CoverReadyToFireCameraHash; //0x02BC
	std::uint32_t RunAndGunCameraHash; //0x02C0
	std::uint32_t CinematicShootingCameraHash; //0x02C4
	std::uint32_t AlternativeOrScopedCameraHash; //0x02C8
	std::uint32_t RunAndGunAlternativeOrScopedCameraHash; //0x02CC
	std::uint32_t CinematicShootingAlternativeOrScopedCameraHash; //0x02D0
	char pad_02D4[4]; //0x02D4
	std::uint32_t RecoilShakeHash; //0x02D8
	std::uint32_t RecoilShakeHashFirstPerson; //0x02DC
	std::uint32_t AccuracyOffsetShakeHash; //0x02E0
	std::int32_t MinTimeBetweenRecoilShakes; //0x02E4
	std::float_t RecoilShakeAmplitude; //0x02E8
	std::float_t ExplosionShakeAmplitude; //0x02EC
	std::float_t CameraFov; //0x02F0
	std::float_t FirstPersonAimFovMin; //0x02F4
	std::float_t FirstPersonAimFovMax; //0x02F8
	char pad_02FC[4]; //0x02FC
	std::float_t FirstPersonScopeFov; //0x0300
	char pad_0304[28]; //0x0304
	std::vector3 FirstPersonRNGOffset; //0x0320
	char pad_032C[4]; //0x032C
	std::vector3 FirstPersonRNGRotationOffset; //0x0330
	char pad_033C[4]; //0x033C
	std::vector3 FirstPersonLTOffset; //0x0340
	char pad_034C[4]; //0x034C
	std::vector3 FirstPersonLTRotationOffset; //0x0350
	char pad_035C[4]; //0x035C
	std::vector3 FirstPersonScopeOffset; //0x0360
	char pad_036C[4]; //0x036C
	std::vector3 FirstPersonScopeAttachmentOffset; //0x0370
	char pad_037C[4]; //0x037C
	std::vector3 FirstPersonScopeRotationOffset; //0x0380
	char pad_038C[4]; //0x038C
	std::vector3 FirstPersonScopeAttachmentRotationOffset; //0x0390
	char pad_039C[4]; //0x039C
	std::vector3 FirstPersonAsThirdPersonIdleOffset; //0x03A0
	char pad_03AC[4]; //0x03AC
	std::vector3 FirstPersonAsThirdPersonRNGOffset; //0x03B0
	char pad_03BC[4]; //0x03BC
	std::vector3 FirstPersonAsThirdPersonLTOffset; //0x03C0
	char pad_03CC[4]; //0x03CC
	std::vector3 FirstPersonAsThirdPersonScopeOffset; //0x03D0
	char pad_03DC[4]; //0x03DC
	std::vector3 FirstPersonAsThirdPersonWeaponBlockedOffset; //0x03E0
	char pad_03EC[4]; //0x03EC
	std::vector3 FirstPersonDofSubjectMagnificationPowerFactorNear; //0x03F0
	char pad_03FC[20]; //0x03FC
	std::float_t ZoomFactorForAccurateMode; //0x0410
	char pad_0414[12]; //0x0414
	std::vector3 AimOffsetMin; //0x0420
	char pad_042C[4]; //0x042C
	std::vector3 AimOffsetMax; //0x0430
	char pad_043C[4]; //0x043C
	Vector2 TorsoAimOffset; //0x0440
	Vector2 TorsoCrouchedAimOffset; //0x0448
	std::float_t AimProbeLengthMin; //0x0450
	std::float_t AimProbeLengthMax; //0x0454
	char pad_0458[8]; //0x0458
	std::vector3 AimOffsetMinFPSIdle; //0x0460
	char pad_046C[4]; //0x046C
	std::vector3 AimOffsetMedFPSIdle; //0x0470
	char pad_047C[4]; //0x047C
	std::vector3 AimOffsetMaxFPSIdle; //0x0480
	char pad_048C[4]; //0x048C
	std::vector3 AimOffsetMinFPSLT; //0x0490
	char pad_049C[4]; //0x049C
	std::vector3 AimOffsetMaxFPSLT; //0x04A0
	char pad_04AC[4]; //0x04AC
	std::vector3 AimOffsetMinFPSRNG; //0x04B0
	char pad_04BC[4]; //0x04BC
	std::vector3 AimOffsetMaxFPSRNG; //0x04C0
	char pad_04CC[4]; //0x04CC
	std::vector3 AimOffsetMinFPSScope; //0x04D0
	char pad_04DC[4]; //0x04DC
	std::vector3 AimOffsetMaxFPSScope; //0x04E0
	char pad_04EC[4]; //0x04EC
	std::vector3 AimOffsetEndPosMinFPSIdle; //0x04F0
	char pad_04FC[4]; //0x04FC
	std::vector3 AimOffsetEndPosMedFPSIdle; //0x0500
	char pad_050C[4]; //0x050C
	std::vector3 AimOffsetEndPosMaxFPSIdle; //0x0510
	char pad_051C[4]; //0x051C
	std::vector3 AimOffsetEndPosMinFPSLT; //0x0520
	char pad_052C[4]; //0x052C
	std::vector3 AimOffsetEndPosMedFPSLT; //0x0530
	char pad_053C[4]; //0x053C
	std::vector3 AimOffsetEndPosMaxFPSLT; //0x0540
	char pad_054C[36]; //0x054C
	std::vector3 LeftHandIkOffset; //0x0570
	char pad_057C[12]; //0x057C
	std::float_t IkRecoilDisplacementScaleBackward; //0x0588
	std::float_t IkRecoilDisplacementScaleVertical; //0x058C
	char pad_0590[16]; //0x0590
	std::float_t ReticuleMinSizeStanding; //0x05A0
	std::float_t ReticuleMinSizeCrouched; //0x05A4
	std::float_t ReticuleScale; //0x05A8
	char pad_05AC[28]; //0x05AC
	std::int8_t AmmoDiminishingRate; //0x05C8
	std::int8_t HudDamage; //0x05C9
	std::int8_t HudSpeed; //0x05CA
	std::int8_t HudCapacity; //0x05CB
	std::int8_t HudAccuracy; //0x05CC
	std::int8_t HudRange; //0x05CD
	char pad_05CE[2]; //0x05CE
	std::float_t AimingBreathingAdditiveWeight; //0x05D0
	std::float_t FiringBreathingAdditiveWeight; //0x05D4
	std::float_t StealthAimingBreathingAdditiveWeight; //0x05D8
	std::float_t StealthFiringBreathingAdditiveWeight; //0x05DC
	std::float_t AimingLeanAdditiveWeight; //0x05E0
	std::float_t FiringLeanAdditiveWeight; //0x05E4
	std::float_t StealthAimingLeanAdditiveWeight; //0x05E8
	std::float_t StealthFiringLeanAdditiveWeight; //0x05EC
	std::float_t ExpandPedCapsuleRadius; //0x05F0
	char pad_05F4[4]; //0x05F4
	std::int32_t KnockdownCount; //0x05F8
	std::float_t KillshotImpulseScale; //0x05FC
	std::uint32_t NmShotTuningSet; //0x0600
	char pad_0604[796]; //0x0604
	std::float_t VehicleAttackAngle; //0x0920
	std::float_t TorsoIKAngleLimit; //0x0924
	char pad_0928[56]; //0x0928

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
}; //Size: 0x0960

class CWeapon
{
public:
	char pad_0008[56]; //0x0008
	class CWeaponInfo* WeaponInfo; //0x0040
	char pad_0048[888]; //0x0048

	virtual void Function0();
	virtual void Function1();
}; //Size: 0x03C0

class CPedWeaponManager
{
public:
	char pad_0008[8]; //0x0008
	std::uint64_t ParentPed; //0x0010
	char pad_0018[80]; //0x0018
	class CWeaponInfo* WeaponInfo; //0x0068
	char pad_0070[8]; //0x0070
	std::uint64_t WeaponObject; //0x0078
	char pad_0080[8]; //0x0080
	class CWeapon* Weapon; //0x0088
	char pad_0090[288]; //0x0090
	std::vector3 LastBulletImpact; //0x01B0
	char pad_01BC[20]; //0x01BC

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
}; //Size: 0x01D0

class CHandlingData
{
public:
	uint32_t handlingName; //0x0008
	float fMass; //0x000C
	float fInitialDragCoeff; //0x0010
	float fDownforceModifier; //0x0014
	float N00000AD9; //0x0018
	float N00000C27; //0x001C
	Vector3 vecCentreOfMassOffset; //0x0020
	float N00000ADC; //0x002C
	Vector3 vecInertiaMultiplier; //0x0030
	float N00000A49; //0x003C
	float fPercentSubmerged; //0x0040
	float fSubmergedRatio; //0x0044
	float fDriveBiasFront; //0x0048
	float fDriveBiasRear; //0x004C
	int32_t nInitialDriveGears; //0x0050
	float fDriveInertia; //0x0054
	float fClutchChangeRateScaleUpShift; //0x0058
	float fClutchChangeRateScaleDownShift; //0x005C
	float fInitialDriveForce; //0x0060
	float fDriveMaxFlatVel; //0x0064
	float fInitialDriveMaxFlatVel; //0x0068
	float fBrakeForce; //0x006C
	float N000009D5; //0x0070
	float fBrakeBiasFront; //0x0074
	float fBrakeBiasRear; //0x0078
	float N000009C5; //0x007C
	float fSteeringLock; //0x0080
	float fSteeringLockRatio; //0x0084
	float fTractionCurveMax; //0x0088
	float fTractionCurveMaxRatio; //0x008C
	float fTractionCurveMin; //0x0090
	float fTractionCurveRatio; //0x0094
	float fTractionCurveLateral; //0x0098
	float fTractionCurveLateralRatio; //0x009C
	float fTractionSpringDeltaMax; //0x00A0
	float fTractionSpringDeltaMaxRatio; //0x00A4
	float fLowSpeedTractionLossMult; //0x00A8
	float fCamberStiffness; //0x00AC
	float fTractionBiasFront; //0x00B0
	float fTractionBiasRear; //0x00B4
	float fTractionLossMult; //0x00B8
	float fSuspensionForce; //0x00BC
	float fSuspensionCompDamp; //0x00C0
	float fSuspensionReboundDamp; //0x00C4
	float fSuspensionUpperLimit; //0x00C8
	float fSuspensionLowerLimit; //0x00CC
	float fSuspensionRaise; //0x00D0
	float fSuspensionBiasFront; //0x00D4
	float fSuspensionBiasRear; //0x00D8
	float fAntiRollBarForce; //0x00DC
	float fAntiRollBarBiasFront; //0x00E0
	float fAntiRollBarBiasRear; //0x00E4
	float fRollCentreHeightFront; //0x00E8
	float fRollCentreHeightRear; //0x00EC
	float fCollisionDamageMult; //0x00F0
	float fWeaponDamageMult; //0x00F4
	float fDeformationDamageMult; //0x00F8
	float fEngineDamageMult; //0x00FC
	float fPetrolTankVolume; //0x0100
	float fOilVolume; //0x0104
	float N00000AAC; //0x0108
	float fSeatOffsetDistX; //0x010C
	float fSeatOffsetDistY; //0x0110
	float fSeatOffsetDistZ; //0x0114
	int32_t nMonetaryValue; //0x0118
	float N00000AC2; //0x011C
	float N000009D9; //0x0120
	uint32_t strModelFlags; //0x0124
	uint32_t strHandlingFlags; //0x0128
	uint32_t strDamageFlags; //0x012C
	char pad_0130[512]; //0x0130

	virtual void Function0();
	virtual void Function1();
}; //Size: 0x0330

class simple_timer {
private:
	std::uint64_t m_ready_at;
	bool m_tick;
public:
	void start(std::uint64_t ticks) {
		if (this->m_tick) {
			this->m_ready_at = GetTickCount64() + ticks;
			this->m_tick = false;
		}
	}
	bool is_ready() {
		return GetTickCount64() > this->m_ready_at;
	}
	void reset() {
		this->m_tick = true;
	}
};

class ListPool {
public:
	std::uint64_t* list; //0x0000
	std::int32_t capacity; //0x0008
	char pad_000C[4]; //0x000C
	std::int32_t free; //0x0010
	char pad_0014[4]; //0x0014
	std::uint64_t item_size; //0x0018
	char pad_0020[16]; //0x0020
	std::uint32_t* data; //0x0030
	char pad_0038[16]; //0x0038
	std::int32_t occupied; //0x0048

	const std::uint64_t get(std::int32_t index) const {
		if ((this->data[index >> 5] >> (index & 0x1F)) & 1)
			return this->list[index];
		return NULL;
	}

}; //Size: 0x004C

