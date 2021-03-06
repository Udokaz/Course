// Copyright Jacob Humrich 2016

#include "Rooms.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponet();

	SetupInputComponet();

}

///look for attached physics handle
void UGrabber::FindPhysicsHandleComponet()
{
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		///physicsHanlde found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle for $s Not Found!\n"), *GetOwner()->GetName());
	}
}

///look for inputHandler component (only appers at run time)
void UGrabber::SetupInputComponet()
{
	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputHanler found!\n"));
		//bind the input access
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseKey);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputHanler for $s Not Found!\n"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//if the physics is attached
		//move the object we are holding

	/// Get Player Viewport this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	/// red point
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	/// Setup Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray_casting (line trace) to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	
	/// see what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Line Hit: %s "), *(ActorHit->GetName()));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed pressed "));

	//try and reach any actors with physics body collision channel set

	//if we hit something attach physics handle
	//TODO attach physics handl

}

void UGrabber::ReleaseKey()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed Released "));
	///TODO release physics handle

}
