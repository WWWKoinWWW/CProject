
## 겹침 이벤트
* Overlap이 발생했을 때
```
	OnActorBeginOverlap.AddUniqueDynamic(this, &APlayerCharacter::OnActorBeginOverlapEvent);
```
* Overlap이 끝났을 때
```
	OnActorEndOverlap.AddUniqueDynamic(this, &APlayerCharacter::OnActorEndOverlapEvent);
```
