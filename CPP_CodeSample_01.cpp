/*
This sample code is from my Monsieur Monet project, 
a 3rd person stealth game student project.

This is part of the aiming system -- the projectile trajectory path.

by Czarina Ramos
*/

void AMonsieurMonet_Character::TickAim()
{
    //null check for world
	UWorld* world = GetWorld();
	if (world == nullptr)
	{
		return;
	}

    //  Unreal's Predicting Projectile Trajectory path 
	FHitResult Hit;
	TArray<FVector> OutPathPos;
	FVector LastPos;
	FVector StartPos = LureStart->GetComponentLocation();
	FVector CamFVector = PlayerCamera->GetForwardVector();
	FVector LaunchVel = CamFVector * 2500.0F; //LaunchVel = (get forward vector of camera) * (custom speed)
	const TArray<AActor*> ActorsIgnored;

	UGameplayStatics::Blueprint_PredictProjectilePath_ByTraceChannel(
        world, Hit, OutPathPos, LastPos, StartPos, LaunchVel,
		true, 20.0F, ECollisionChannel::ECC_GameTraceChannel1, false,
		ActorsIgnored, EDrawDebugTrace::None, 0.0F);

    //if the raycast did not hit anything within the Available actors
	if (Hit.bBlockingHit == false)
	{
        //disable the end decal and the visualized previous points
		TargetEndDecal->SetVisibility(false);
		VisualizedAim->SetVisibility(false);
		return;
	}

	//if hit is true:
	FTransform item;
	item.SetLocation((Hit.ImpactPoint));
	FRotator rot = FRotationMatrix::MakeFromX(Hit.ImpactNormal).Rotator();
	item.SetRotation(rot.Quaternion());

    //shows the end target and sets it at the hit point
	TargetEndDecal->SetWorldTransform(item);
	TargetEndDecal->SetVisibility(true);
	AimTargetPos = Hit.ImpactPoint;
    
    //for printing and debugging purposes
	// ProjVel = LaunchVel;
	// HitArray = OutPathPos;

    //check if the script should be showing the trajectory or not
	if (showVisualizedAimCPP == false)
	{
		return;
	}

	VisualizedAim->SetVisibility(true);

	//gets current number of visible dots
	CurrentAimInst = VisualizedAim->GetInstanceCount();

	CurrentHitNum = OutPathPos.Num();

	FTransform transform;
	transform.SetLocation(FVector::ZeroVector);
	transform.SetRotation(FRotator::ZeroRotator.Quaternion());
	transform.SetScale3D(FVector::ZeroVector);

	if (CurrentAimInst < CurrentHitNum)
	{
		//adds more instances based on difference on needed instances
		int32 difference = CurrentHitNum - CurrentAimInst;
		for (int32 i = 0; i < difference; i++)
		{
			VisualizedAim->AddInstanceWorldSpace(transform);
		}
	}

	//sets the visual aim positions
	for (int32 j = 0; j < CurrentHitNum; j++)
	{
		FTransform trans;
		trans.SetLocation(OutPathPos[j]);
		trans.SetRotation(FRotator::ZeroRotator.Quaternion());
		trans.SetScale3D(FVector(0.2F, 0.2F, 0.2F)); //set current size for the dots
		VisualizedAim->UpdateInstanceTransform(j, trans, true, true, true);
	}

	//sets the visual aim positions of unused ones
	if (CurrentHitNum < CurrentAimInst)
	{
		for (int32 k = CurrentHitNum; k < VisualizedAim->GetInstanceCount(); k++)
		{
			VisualizedAim->UpdateInstanceTransform(k, transform, true, false, true);
		}
	}
}