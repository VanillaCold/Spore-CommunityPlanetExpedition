######################################################################
# General Moments

state CRG_MomentButton
  wait -forButton
  setExitState CRG_MomentCameraRevert
   nextState CRG_MomentCameraRevert
end

state CRG_MomentCameraRevert
   disableEscExit
   unpauseGame
   setExitState null
   letterbox -off
   text -hide
   startCamera -backToStart -duration .35
end   

state CRG_SnapMomentButton
  wait -forButton
   setExitState CRG_SnapMomentCameraRevert
   nextState CRG_SnapMomentCameraRevert
end

state CRG_SnapMomentCameraRevert
   disableEscExit
   unpauseGame
   letterbox -off
   setExitState null
   text -hide
   startCamera -backToStart -snap
end   

#--------------------------------
# FirstDNA 
state CRG_FirstDNA
   description "Earning DNA Points"
   letterbox -on
   mixevent crg_cin_start 1
   alphaObstacles on -camera -actors "TheAvatar" -radius 10.0 -types all
   addActor "TheAvatar" avatar
   startCamera -offset 10 -useRadius -useFootprint -target "TheAvatar" -targetOffset (0, 0, 1.75) -pitch 0 -snap -noWait -fov .8
   wait -secs 2.68
   nextState CRG_FirstDNA2
end

state CRG_FirstDNA2
  pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   nextState CRG_FirstDNA3
end

state CRG_FirstDNA3
   wait -secs 1
   textFromCode "FirstDNAString"
   nextState CRG_MomentButton
end

#--------------------------------
# FirstPartUnlock 
state CRG_FirstPartUnlock
   letterbox -on
   addActor "TheAvatar" avatar
   alphaObstacles on -camera -actors "TheAvatar" -radius 10.0 -types all
   startCamera -offset 10 -target "TheAvatar" -targetOffset (0, 0, 1.75) -pitch 0 -snap -noWait -fov .8
   wait -secs 1.5
   nextState CRG_FirstPartUnlock2
end

state CRG_FirstPartUnlock2
   pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   nextState CRG_FirstPartUnlock2b
end

state CRG_FirstPartUnlock2b
   text "When a new part is discovered through combat or socialization, it opens a potential evolutionary path for future generations to follow. You can use newly opened parts the next time you visit the Creature Editor" cinematics_crg!0x04599f0f
   wait -secs 1
   nextState CRG_MomentButton
end

#--------------------------------

# FirstPosse 
state CRG_FirstPosse
   description "Posse"
   letterbox -on
   mixevent crg_cin_start 1
   addActor "avatar" avatar
   addActor "posse" posse
   alphaObstacles on -camera -actors "avatar" -radius 10.0 -types all
   playAnimation "avatar" (0x065fc866) -noWait
   startCamera -offset 11 -useRadius -useFootprint -target "avatar" -targetOffset (0, 0, 1) -pitch -.02 -heading .47 -orient -snap -noWait 
   nextState CRG_FirstPosse1
end

state CRG_FirstPosse1
   playAnimation "posse" (0x065fc891) -noWait   
   startCamera -offset 11 -useRadius -useFootprint -target "avatar" -targetOffset (0, 0, 1) -pitch -.02 -heading .53 -orient -duration 2.5 -noWait
   wait -secs 2.5
   nextState CRG_FirstPosse2
end

state CRG_FirstPosse2
   startCamera -offset 11 -useRadius -useFootprint -target "posse" -targetOffset (0, 0, 1) -pitch -.02 -heading .53 -orient -snap -noWait
   nextState CRG_FirstPosse3
end

state CRG_FirstPosse3
  startCamera -offset 11 -useRadius -useFootprint -target "posse" -targetOffset (0, 0, 1) -pitch -.02 -heading .59 -orient -duration 2.5 -noWait
  wait -secs 3
  nextState CRG_FirstPosseA
end

state CRG_FirstPosseA
   pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   nextState CRG_FirstPosseB
end

state CRG_FirstPosseB
   text "Evolution is a task best suited to pairs, but additional company never hurts. Creatures who join your posse will follow you and help out. Why? That's just how your posse rolls." cinematics_crg!0x04599f10
   wait -secs 1
   nextState CRG_SnapMomentButton
end

# SocialFailure 
state CRG_SocialFailure
   description "Social Failure"
   letterbox -on
   mixevent crg_cin_start 1
   pauseGame
   text "Social Failure" cinematics_crg!0x93e071dc
   wait -forButton
   nextState CRG_MomentCameraRevert
end

#-----------------------------------
# TargetedCreature
state CRG_TargetedCreature
   letterbox -on
   addActor "targetNPC" targetNPC
   mixevent crg_cin_start 1
   alphaObstacles on -camera -actors "targetNPC" -radius 8.0 -types all
   startCamera -offset 5 -targetOffset (0, 0, .5) -useRadius -useFootprint -target "targetNPC" -noWait -duration .6
   playAnimation "targetNPC" (0x05c05d22) 
   wait -secs 2
   nextState CRG_TargetedCreature2
end

state CRG_TargetedCreature2
   pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   nextState CRG_TargetedCreature3
end

state CRG_TargetedCreature3
   text "You can forge relationships with the other creatures and tribes of your world. Reach out peacefully to make temporary allies, or reach out and give somebody a smack upside the head. Both interactions earn DNA points." cinematics_crg!0x04599f12
   wait -secs 1
   nextState CRG_SnapMomentButton
end

######################################################################
#### Start Migration ###

state CRG_SpeciesMigrate
   description "CRG_SpeciesMigrate"
   letterbox -on
   mixevent crg_migrate_mix 1
   startsound music_crg_migrate -escstop
   startEffect "fadeIn" fade_from_black_quick -noWait
   # add actors
   addActor "TheAvatar" avatar
   addActor "Actor1" playerSpecies -initialRelativePosition object "teacher" (2.5, 0, 0)
   addActor "Actor2" playerSpecies -initialRelativePosition object "AvatarNest" (2.5, 2.5, 0)
   addActor "Actor3" playerSpecies -initialRelativePosition object "AvatarNest" (2.5, -2.5, 0)
   addActor "Actor4" playerSpecies -initialRelativePosition object "AvatarNest" (0, 5, 0)
   addActor "Actor5" playerSpecies -initialRelativePosition object "AvatarNest" (0, -5, 0)
   # put them in place
   moveActor "Actor1" (0, 0, 0) -relative actor "Actor1" -face object "AvatarNest" -snap
   moveActor "Actor2" (0, 0, 0) -relative actor "Actor2" -face object "AvatarNest" -snap
   moveActor "Actor3" (0, 0, 0) -relative actor "Actor3" -face object "AvatarNest" -snap
   moveActor "Actor4" (0, 0, 0) -relative actor "Actor4" -face object "AvatarNest" -snap
   moveActor "Actor5" (0, 0, 0) -relative actor "Actor5" -face object "AvatarNest" -snap
   # set camera
   alphaObstacles on -camera -radius 6.0 -types all
   startCamera -offset 4 -target "teacher" -targetOffset (0, 0, .5) -orient -pitch -.07 -heading .5 -snap -noWait -fov .75
   setExitState CRG_SpeciesMigrate_Done
   nextState CRG_SpeciesMigrate_setup
end

state CRG_SpeciesMigrate_setup
   startCamera -anchored -target "egg" -snap -targetOffset (0, 0, 1) -useRadius -noWait -fov .8
   nextState CRG_SpeciesMigrate_setup1
end

state CRG_SpeciesMigrate_setup1
   startCamera -anchored -offset -12 -target "egg" -targetOffset (0, 0, 1) -useRadius -duration 3.5 -noWait -fov .75
   wait -secs 3
   nextState CRG_SpeciesMigrate_WalkActors
end

state CRG_SpeciesMigrate_WalkActors
   description "CRG_SpeciesMigrate_WalkActors"
   playAnimation "Actor1" (0x065652d4 0x065652d1) -noWait # bay and walk
   playAnimation "Actor2" (0x065652d1) -noWait # walk 
   playAnimation "Actor3" (0x065652d1) -noWait # walk 
   playAnimation "Actor4" (0x065652d1) -noWait # walk
   playAnimation "Actor5" (0x065652d1) -noWait # bay a few times and walk
   moveActor "Actor1" (0, 0, 0) -relative object "DestinationNest" -noWait
   moveActor "Actor2" (0, 0, 0) -relative object "DestinationNest" -noWait
   moveActor "Actor3" (0, 0, 0) -relative object "DestinationNest" -noWait
   moveActor "Actor4" (0, 0, 0) -relative object "DestinationNest" -noWait
   moveActor "Actor5" (0, 0, 0) -relative object "DestinationNest" -noWait
   wait -secs .5
   nextState CRG_SpeciesMigrate_WalkActors0
end

state CRG_SpeciesMigrate_WalkActors0
   startCamera -useRadius -useFootprint -target "Actor1" -targetOffset (0, 0, 0.65) -snap -noWait -orient -pitch -.06 -heading 0 -offset 5 -follow -fov .75
   nextState CRG_SpeciesMigrate_WalkActors1
end

state CRG_SpeciesMigrate_WalkActors1
   startCamera -useRadius -useFootprint -target "Actor1" -targetOffset (0, 0, 0.65) -offset 1 -anchored -duration 2 -follow -sphere -fov .75
   wait -secs 3
   stateDuration 6
   nextState CRG_SpeciesMigrate_Wave1
end

state CRG_SpeciesMigrate_Wave1
   description "CRG_SpeciesMigrate_Wave1"
   moveActor "Actor1" (0, 0, 0) -relative actor "Actor1" -face actor "teacher"
   moveActor "teacher" (0, 0, 0) -relative actor "teacher" -face actor "Actor1"
   nextState CRG_SpeciesMigrate_Wave2
end

state CRG_SpeciesMigrate_Wave2
   description "CRG_SpeciesMigrate_Wave2"
   playAnimation "Actor1" (0x065652d0) -noWait # wave at mom
   startCamera -offset 5 -useRadius -useFootprint -target "Actor1" -targetHead -orient -heading 0.45 -pitch -0.03 -snap -noWait -sphere -fov .75
   nextState CRG_SpeciesMigrate_Wave2b
end

state CRG_SpeciesMigrate_Wave2b
   startCamera  -offset 5.5 -useRadius -useFootprint -target "Actor1" -targetHead -orient -heading 0.45 -pitch -0.03 -duration 4 -noWait -sphere -fov .75
   wait -secs 3.5
   nextState CRG_SpeciesMigrate_Wave3
end

state CRG_SpeciesMigrate_Wave3
   startCamera -offset 6 -useRadius -useFootprint -target "teacher" -targetHead -orient -heading 0.55 -pitch 0 -snap -noWait -fov .75
   nextState CRG_SpeciesMigrate_Wave3b
end

state CRG_SpeciesMigrate_Wave3b
   startCamera -offset 6.5 -useRadius -useFootprint -target "teacher" -targetHead -orient -heading 0.55 -pitch 0 -duration 5 -noWait -sphere -fov .75
   playAnimation "teacher" (0x065659aa) # wave at other   
   nextState CRG_SpeciesMigrate_MomTurn
end

state CRG_SpeciesMigrate_MomTurn
   description "CRG_SpeciesMigrate_MomTurn"
   moveActor "teacher" (0, 0, 0) -relative actor "teacher" -face object "AvatarNest"
   moveActor "Actor1" (0, 0, 0) -relative object "DestinationNest" -noWait
   nextState CRG_SpeciesMigrate_MomTurn1
end

state CRG_SpeciesMigrate_MomTurn1
   startCamera -offset 6 -useRadius -useFootprint -target "teacher" -targetHead -orient -heading 0.65 -pitch -.05 -snap -noWait -fov .75
   nextState CRG_SpeciesMigrate_Mom
end

state CRG_SpeciesMigrate_Mom
   description "CRG_SpeciesMigrate_Mom"
   playAnimation "teacher" (0x065659af)  # look at baby
   startCamera -target "Egg" -targetOffset (0, 0, 1) -useRadius -anchored -duration 7.0 -noWait -fov .75
   nextState CRG_SpeciesMigrate_Hatch
end

state CRG_SpeciesMigrate_Hatch
   description "CRG_SpeciesMigrate_Hatch"
   sendMessage -id 0x06566531 # kHatchAvatarEggs
   letAIRun
   startCamera -target "TheAvatar" -targetOffset (0, 0, 1) -useRadius -offset -18 -anchored -duration 10 -noWait -fov .75
   wait -secs 10
   nextState CRG_SpeciesMigrate_Pause
end

state CRG_SpeciesMigrate_Pause
   description "CRG_SpeciesMigrate_Pause"
   pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   setExitState CRG_SpeciesMigrate_Done
   nextState CRG_SpeciesMigrate_Text
end

state CRG_SpeciesMigrate_Text
   description "CRG_SpeciesMigrate_Text"
   wait -secs 1
   text "Claiming a new nest." cinematics_crg!0x04599f1a
   nextState CRG_SpeciesMigrate_WaitForButton
end

state CRG_SpeciesMigrate_WaitForButton
   description "CRG_SpeciesMigrate_WaitForButton"
   wait -forButton
   nextState CRG_SpeciesMigrate_Done
end

state CRG_SpeciesMigrate_Done
   # just in case the user pressed escape
   mixevent crg_migrate_mix 0
   sendMessage -id 0x06566531 # kHatchAvatarEggs
   startCamera -target "TheAvatar" -targetOffset (0, 0, 1) -useRadius -offset -18 -orient -heading 0.65 -pitch -.05 -anchored -snap -noWait -fov .75
   preserveCinematicCamView
end

######################################################################
##### Claim Nest ####

state CRG_ClaimNest
   letterbox -on
   setExitState CRG_ClaimNest_Done
   mixevent crg_migrate_mix 1
   startsound music_crg_claimnest -escstop
   unpauseGame
   # add actors
   addActor "TheAvatar" avatar -initialRelativePosition actorNest "TheAvatar" (-20, 0, 0)
   addActor "Actor1" playerSpecies -initialRelativePosition actorNest "TheAvatar" (3, .5, 0)
   addActor "Actor2" playerSpecies -initialRelativePosition actorNest "TheAvatar" (2.5, 2, 0)
   addActor "Actor3" playerSpecies -initialRelativePosition actorNest "TheAvatar" (2.5, -3.5, 0)
   addActor "Actor4" playerSpecies -initialRelativePosition actorNest "TheAvatar" (0, 3.3, 0)
   addActor "Actor5" playerSpecies -initialRelativePosition actorNest "TheAvatar" (1, -3, 0)
   # put them in place
   moveActor "TheAvatar" (0, 0, 0) -relative actor "TheAvatar" -face actorNest "TheAvatar" -snap
   moveActor "Actor1" (0, 0, 0) -relative actor "Actor1" -face actor "TheAvatar" -snap
   moveActor "Actor2" (0, 0, 0) -relative actor "Actor2" -face actor "TheAvatar" -snap
   moveActor "Actor3" (0, 0, 0) -relative actor "Actor3" -face actor "TheAvatar" -snap
   moveActor "Actor4" (0, 0, 0) -relative actor "Actor4" -face actor "TheAvatar" -snap
   moveActor "Actor5" (0, 0, 0) -relative actor "Actor5" -face actor "TheAvatar" -snap
   alphaObstacles on -camera -actors "TheAvatar" -radius 10.0 -types all
   
   # add nest object
   addObject "AvatarNest" -initialRelativePosition actorNest "TheAvatar" (0, 0, 0) -face actorNest "TheAvatar" (0, 0, 0)
   
   startCamera -offset 8 -useRadius -useFootprint -target "TheAvatar" -targetOffset (0, 4, .5) -orient -heading 0 -pitch -.1 -snap -noWait -follow -fov .75
   nextState CRG_ClaimNest_Arrival
end

state CRG_ClaimNest_Arrival
   startsound sfx_crg_cin_nest_claim_foley
   # move avatar and have everyone beckon it and then turn and face the nest
   moveActor "TheAvatar" (0, 0, 0) -relative actorNest "TheAvatar" -face actorNest "TheAvatar"
   playAnimation "Actor1" (0x06550c51) -noWait
   playAnimation "Actor2" (0x06550c51) -noWait
   playAnimation "Actor3" (0x06550c51) -noWait
   playAnimation "Actor4" (0x06550c51) -noWait
   playAnimation "Actor5" (0x06550c51) -noWait
   moveActor "Actor1" (0, 0, 0) -relative actor "Actor1" -face actorNest "TheAvatar"
   moveActor "Actor2" (0, 0, 0) -relative actor "Actor2" -face actorNest "TheAvatar"
   moveActor "Actor3" (0, 0, 0) -relative actor "Actor3" -face actorNest "TheAvatar"
   moveActor "Actor4" (0, 0, 0) -relative actor "Actor4" -face actorNest "TheAvatar"
   moveActor "Actor5" (0, 0, 0) -relative actor "Actor5" -face actorNest "TheAvatar"
   startCamera -useRadius -useFootprint -target "TheAvatar" -targetOffset (0, 1, .5) -anchored -duration 3 -noWait -follow -sphere -fov .75
   nextState CRG_ClaimNest_Cheer1
end

state CRG_ClaimNest_Cheer1
   startCamera -useRadius -useFootprint -target "TheAvatar" -targetOffset (0, 1, .5)  -offset 8 -orient -snap -pitch -.05 -heading -.15 
   nextState CRG_ClaimNest_Cheer2
end


state CRG_ClaimNest_Cheer2
   playAnimation "TheAvatar" (0x06550c81)
   playAnimation "Actor1" (0x06550c81) -noWait
   playAnimation "Actor2" (0x06550c82) -noWait
   playAnimation "Actor3" (0x06550c82) -noWait
   playAnimation "Actor4" (0x06550c83) -noWait
   playAnimation "Actor5" (0x06550c83) -noWait
   startCamera -useRadius -useFootprint -target "TheAvatar" -targetOffset (0, 2, .5)  -offset 10 -orient -duration 10 -pitch -.05 -heading .6 -noWait
   nextState CRG_ClaimNest_Build1
end

state CRG_ClaimNest_Build1
   startCamera -useRadius -useFootprint -target "TheAvatar" -targetOffset (0, 2, .5)  -offset 12 -orient -snap -pitch -.05 -heading .5 -noWait
   nextState CRG_ClaimNest_Build2
end

state CRG_ClaimNest_Build2
#  startEffect "crg_nest_claim" crg_nest_claim -target "AvatarNest" -noWait
# commenting this out.  the correct effect is playing in the next state
   playAnimation "TheAvatar" (0x06550c71)
   playAnimation "Actor1" (0x06550c71) -noWait
   playAnimation "Actor2" (0x06550c72) -noWait
   playAnimation "Actor3" (0x06550c73) -noWait
   playAnimation "Actor4" (0x06550c72) -noWait
   playAnimation "Actor5" (0x06550c73) -noWait
   startCamera -useRadius -useFootprint -target "TheAvatar" -targetOffset (0, 2, .5)  -offset 20 -orient -duration 10 -pitch -.1 -heading .5 -noWait   
   nextState CRG_ClaimNest_Dance
end

state CRG_ClaimNest_Dance
   sendMessage -id 0x06555abc  # kUpgradeNest -- this actually swaps out the model
   # play an effect to cover this model swap?
   startEffect "crg_nest_upgrade" crg_nest_upgrade -target "AvatarNest" -noWait
   #play the associated sound for next vfx
   startsound sfx_crg_cin_nest_claim
   # everyone dance!
   playAnimation "TheAvatar" (0x06550c91)
   playAnimation "Actor1" (0x06550c91)
   playAnimation "Actor2" (0x06550c92)
   playAnimation "Actor3" (0x06550c93)
   playAnimation "Actor4" (0x06550c93)
   playAnimation "Actor5" (0x06550c92)
   nextState CRG_ClaimNest_Pause
end

state CRG_ClaimNest_Pause
   pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   setExitState CRG_ClaimNest_Done
   nextState CRG_ClaimNest_Text
end

state CRG_ClaimNest_Text
   wait -secs 1
   text "Claiming a new nest." cinematics_crg!0x0540222f
   setExitState CRG_ClaimNest_Done
   nextState CRG_ClaimNest_WaitForButton
end

state CRG_ClaimNest_WaitForButton
   wait -forButton
   nextState CRG_ClaimNest_Done
end

state CRG_ClaimNest_Done
   # send message upon ESC.  it is okay if we send this multiple times.
   mixevent crg_migrate_mix 0
   sendMessage -id 0x06555abc  # kUpgradeNest
end

####

# End General Moments
######################################################################

######################################################################
# Laid Egg, Enter Editor
# Do not add the avatar as an actor here, it messes up the behavior (calls animation)

state CRG_LaidEgg
   mixevent play_mate_music 1
   letAIRun
   letterbox -on
   alphaObstacles on -camera -actors "MateLead" -radius 8.0 -types all
   startcamera -targetOffset (0, 0, .75) -target "MateLead" -useHeight -follow -orient -pitch -.05 -heading .1 -noWait -offset 6 -snap -fov .75
   setExitState CRG_LaidEggDone2
   nextState CRG_LaidEggA
end

state CRG_LaidEggA
   startcamera -targetOffset (0, 0, .75) -target "MateLead" -useHeight -follow -pitch -.05 -heading .85 -noWait -duration 12 -offset 5 -fov .75
   wait -forContinue
   nextState CRG_LaidEggZoom
end

state CRG_LaidEggZoom
   startcamera -targetOffset (0, 0, .65) -target "MateLead" -useHeight -follow -pitch -.05 -heading .1 -orient -noWait -snap -offset 5 -fov .75
   nextState CRG_LaidEggZoomA
end

state CRG_LaidEggZoomA
   startcamera -target "Egg" -useHeight -targetOffset (0, 0, .75) -noWait -duration 5 -anchored -fov .75
   nextState CRG_LaidEggZoomB
   wait -secs 5
end

state CRG_LaidEggZoomB
   startcamera -target "Egg" -useHeight -targetOffset (0, 0, .75) -noWait -duration 2 -offset 4 -anchored -fov .75
   nextState CRG_LaidEggDone
   wait -secs 1
end

state CRG_LaidEggDone
   startEffect "fadeOut" fade_to_black_quick -noWait
   wait -secs 1
   setExitState CRG_LaidEggDone2
   nextState CRG_LaidEggDone2
end

state CRG_LaidEggDone2
   setExitState null
   mixevent play_mate_music 0
   sendMessage -id 0x04d9686f  # kEnterCreatureEditor
end


######################################################################
# Avatar Died

# This state is triggered if the avatar dies by combat
state CRG_AvatarDied
   description "Avatar Died"
   letterbox -on
   mixevent crg_cin_death 1
   letAIRun  
   addActor "TheAvatar" avatar
   nextState CRG_AvatarDiedA
   setExitState CRG_Death_Restart
end

state CRG_AvatarDiedA
   alphaObstacles on -camera -actors "TheAvatar" -radius 8.0 -types all
   startCamera -offset 5 -useRadius -targetHead -target "TheAvatar" -follow -noWait -pitch -.1 -heading .5 -orient -fov .7 -snap -sphere
   nextState CRG_AvatarDiedC
end

state CRG_AvatarDiedC
   startCamera -useRadius -targetHead -target "TheAvatar" -follow -offset 20 -heading .5 -pitch -.15 -noWait -fov .7 -duration 6 -sphere
   wait -secs 6
   nextState CRG_AvatarDied1
end 

state CRG_AvatarDied1
   pauseGame -screenEffect -effect DeathFreezeFrame -pauseGraphics
   wait -secs .135
   nextState CRG_AvatarDied2
end

state CRG_AvatarDied2
   text "You died." cinematics_crg!0x04599f18
   wait -secs 1
   nextState CRG_AvatarDied3
end

state CRG_AvatarDied3
   wait -forButton
   nextState CRG_Death_Restart
end

#----------------

# This state is triggered if the avatar dies by starvation
state CRG_AvatarDied_Starvation
   description "Avatar Died"
   letterbox -on
   mixevent crg_cin_death 1
   letAIRun  
   addActor "TheAvatar" avatar
   nextState CRG_AvatarDiedA_Starvation
   setExitState CRG_Death_Restart
end

state CRG_AvatarDiedA_Starvation
   alphaObstacles on -camera -actors "TheAvatar" -radius 8.0 -types all
   startCamera -offset 5 -useRadius -targetHead -target "TheAvatar" -follow -noWait -pitch -.1 -heading .5 -orient -fov .7 -snap -sphere
   nextState CRG_AvatarDiedB_Starvation
end

state CRG_AvatarDiedB_Starvation
   startCamera -useRadius -targetHead -target "TheAvatar" -follow -anchored -noWait -fov .7 -snap -sphere
   wait -secs 5
   nextState CRG_AvatarDiedC_Starvation
end 

state CRG_AvatarDiedC_Starvation
   startCamera -useRadius -targetHead -target "TheAvatar" -pitch -.15 -follow -offset 20 -noWait -fov .7 -duration 6 -sphere
   wait -secs 6
   nextState CRG_AvatarDied1_Starvation
end 

state CRG_AvatarDied1_Starvation
   pauseGame -screenEffect -effect DeathFreezeFrame -pauseGraphics
   wait -secs .135
   nextState CRG_AvatarDied2_Starvation
end

state CRG_AvatarDied2_Starvation
   text "You died." cinematics_crg!0x04599f29
   wait -secs 1
   nextState CRG_AvatarDied3_Starvation
end

state CRG_AvatarDied3_Starvation
   wait -forButton
   nextState CRG_Death_Restart
end

#----------------

#state CRG_AvatarDied_SeaMonster
#   startsound music_crg_cin_waterdeath -escstop
#   letterbox -on
#   addActor "TheAvatar" avatar
#   playAnimation "TheAvatar" (0x04767ed9) -noWait  # hide avatar   
##   startcamera -target "TheAvatar" -targetOffset (0, 0, 0) -offset 35 -noWait  -duration 3 -ease -fov .65
#   wait -secs 3
#
#   setExitState CRG_Death_Restart
#   nextState CRG_AvatarDied_SeaMonster0
#end

#state CRG_AvatarDied_SeaMonster0
##   mixevent crg_cin_death 1
#   letterbox -on
#   addActor "TheAvatar" avatar
#   startcamera -target "TheAvatar" -targetOffset (0, 0, 18) -offset 30 -noWait  -duration .65 -fov .65
#   startEffect "crg_seamonster_attack" crg_seamonster_attack -target "TheAvatar" -noWait
#   startEffect "splash1" monster_water_splash -target "TheAvatar" -noWait 
#   wait -secs .65
#   addObject "avatarLocation" -initialRelativePosition actor "TheAvatar" (0, 0, 0) -face actor "TheAvatar" (0, 0, 0)
#   nextState CRG_AvatarDied_SeaMonster1
#end

#state CRG_AvatarDied_SeaMonster1
#   playAnimation "TheAvatar" (0x065e5a8a) -noWait  # hide avatar   
#   moveActor "TheAvatar" (0, 0, 0) -relative actorNest "AvatarNest" -face actorNest "AvatarNest" -snap
#   startcamera -target "avatarLocation" -targetOffset (0, 0, 4.5) -anchored -noWait -duration 1.25 -fov .65
#   wait -secs 1.25

#   nextState CRG_AvatarDied_SeaMonster2
#end

#state CRG_AvatarDied_SeaMonster2
#   wait -secs 1.03

#   nextState CRG_AvatarDied_SeaMonsterFreeze
#end

#state CRG_AvatarDied_SeaMonsterFreeze
#   pauseGame -screenEffect -effect DeathFreezeFrame -pauseGraphics
#   wait -secs .135
#   nextState CRG_AvatarDied_SeaMonsterFreeze1
#end

#state CRG_AvatarDied_SeaMonsterFreeze1
#   text "Sea monster coming to get-cha." cinematics_crg!0x0508c713
#   wait -secs 2
#   nextState CRG_AvatarDied_SeaMonsterFreeze2
#end

#state CRG_AvatarDied_SeaMonsterFreeze2
#   wait -forButton
#   nextState CRG_Death_Restart
#end

###

state CRG_Death_Restart
   description "CRG_Death_Restart"
   unpauseGame # unpause so the effect shows up properly (gets rid of pauseGraphics)
   pauseGame   # pause again so nothing happens
   text -hide
   # this persisting effect needs to be killed by
   # another screen effect--Lydia to add a command to kill persisting effects
   startEffect "black" black_screen -persist -noWait
   sendMessage -id 0x04f60b92  # kRestartAtNest
   setExitState null
end

###

state CRG_Fade_From_Black_Egg
   letterbox -on
   letAIRun
   addActor "TheAvatar" avatar
   startEffect "fadeIn" fade_from_black_1 -noWait
   startCamera -offset 3 -targetOffset (0, 0, .25) -target "egg" -orient -pitch -.03 -heading -.15 -snap -noWait
   nextState CRG_Fade_From_Black_EggB
end

state CRG_Fade_From_Black_EggB
   startCamera -offset 9 -targetOffset (0, 0, .25) -target "egg" -orient -pitch -.1 -heading .15 -duration 10 -noWait -ease
   wait -secs 10
   preserveCinematicCamView
end
 
# End Avatar Died
######################################################################

######################################################################
# Brain Upgrade Moments

state CRG_BrainUpgrade1
   description "Brain Upgrade 1"
   addActor "TheAvatar" avatar
   alphaObstacles on -camera -actors "TheAvatar" -radius 8.0 -types all
   letAIRun -avatarOnly
   startEffect "fadeOut" fade_to_black_quick -noWait
   nextState CRG_BrainUpgrade1a
   startsound music_brain_upgrade -escStop
   wait -secs 1
end

state CRG_BrainUpgrade1a
   letterbox -on
   clearAreaAroundObject "TheAvatar" 10.0 -animals -snap   
   startEffect "fadeIn" fade_from_black_quick -noWait
   nextState CRG_BrainUpgrade1b
   startcamera -target "TheAvatar" -targetHead -orient -offset 7 -useRadius -pitch -.05 -heading 0.5 -fov .8 -snap -noWait
end

state CRG_BrainUpgrade1b
   nextState CRG_BrainUpgrade1c
   wait -forContinue
   startcamera -target "TheAvatar" -targetHead -orient -offset 6 -duration 10 -useRadius -pitch -.05 -heading 0.5 -fov .8 -noWait
end

state CRG_BrainUpgrade1c
   letAIRun -stop
   playAnimation "TheAvatar" 0x0541ba87 # gen_brainup_admire
   nextState CRG_BrainUpgrade1d
end

state CRG_BrainUpgrade1d
   playAnimation "TheAvatar" 0x05405ea1 # gen_brainup_idle_1
   nextState CRG_BrainUpgrade1e
end

state CRG_BrainUpgrade1e
   playAnimation "TheAvatar" 0x05d2bc4a # gen_brainup_react_v1
   nextState CRG_BrainUpgrade1f
end

state CRG_BrainUpgrade1f
   playAnimation "TheAvatar" 0x054075a4 # gen_brainup_celebrate_01
   nextState CRG_BrainUpgrade1g
end

state CRG_BrainUpgrade1g
   stopsound music_brain_upgrade
   stopCamera
  pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   nextState CRG_BrainUpgrade1h
end

state CRG_BrainUpgrade1h
   text "Congratulations! Your creature's brain has evolved to a new level.  You have gained a posse slot." cinematics_crg!0x054076aa
   wait -secs 1
   nextState CRG_BrainUpgrade1i
end

state CRG_BrainUpgrade1i
   wait -forButton
end


####

state CRG_BrainUpgrade2
   description "Brain Upgrade 2"
   addActor "TheAvatar" avatar
   letAIRun -avatarOnly
   startEffect "fadeOut" fade_to_black_quick -noWait
   nextState CRG_BrainUpgrade2a
   startsound music_brain_upgrade -escStop
   alphaObstacles on -camera -actors "TheAvatar" -radius 8.0 -types all
   wait -secs 1
end

state CRG_BrainUpgrade2a
   letterbox -on
   clearAreaAroundObject "TheAvatar" 10.0 -animals -snap   
   startEffect "fadeIn" fade_from_black_quick -noWait
   nextState CRG_BrainUpgrade2b
   startcamera -target "TheAvatar" -targetHead -orient -offset 7 -useRadius -pitch -.05 -heading 0.5 -fov .8 -snap -noWait
end

state CRG_BrainUpgrade2b
   nextState CRG_BrainUpgrade2c
   wait -forContinue
   startcamera -target "TheAvatar" -targetHead -orient -offset 6 -duration 10 -useRadius -pitch -.05 -heading 0.5 -fov .8 -noWait
end

state CRG_BrainUpgrade2c
   letAIRun -stop
   playAnimation "TheAvatar" 0x0541ba87 # gen_brainup_admire
   nextState CRG_BrainUpgrade2d
end

state CRG_BrainUpgrade2d
   playAnimation "TheAvatar" 0x055ac810 # gen_brainup_idle_2
   nextState CRG_BrainUpgrade2e
end

state CRG_BrainUpgrade2e
   playAnimation "TheAvatar" 0x05d2bc4b # gen_brainup_react_v2
   nextState CRG_BrainUpgrade2f
end

state CRG_BrainUpgrade2f
   playAnimation "TheAvatar" 0x05597645 # gen_brainup_celebrate_02
   nextState CRG_BrainUpgrade2g
end

state CRG_BrainUpgrade2g
   stopsound music_brain_upgrade
   stopCamera
   pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   nextState CRG_BrainUpgrade2h
end

state CRG_BrainUpgrade2h
   text "Another step towards sentience...  Your brain is larger, your stature grander!  ~br~You can now add a second creature to your pack!" cinematics_crg!0x0541b1d1
   wait -secs 1
   nextState CRG_BrainUpgrade2i
end

state CRG_BrainUpgrade2i
   wait -forButton
end

####

state CRG_BrainUpgrade3
   description "Brain Upgrade 3"
   addActor "TheAvatar" avatar
   letAIRun -avatarOnly
   nextState CRG_BrainUpgrade3a
   startsound music_brain_upgrade -escStop
   startEffect "fadeOut" fade_to_black_quick -noWait
   alphaObstacles on -camera -actors "TheAvatar" -radius 8.0 -types all
   wait -secs 1   
end

state CRG_BrainUpgrade3a
   letterbox -on
   clearAreaAroundObject "TheAvatar" 10.0 -animals -snap   
   startEffect "fadeIn" fade_from_black_quick -noWait
   nextState CRG_BrainUpgrade3b
   startcamera -target "TheAvatar" -targetHead -orient -offset 7 -useRadius -pitch -.05 -heading 0.5 -fov .8 -snap -noWait
end

state CRG_BrainUpgrade3b
   nextState CRG_BrainUpgrade3c
   wait -forContinue
   startcamera -target "TheAvatar" -targetHead -orient -offset 6 -duration 10 -useRadius -pitch -.05 -heading 0.5 -fov .8 -noWait
end

state CRG_BrainUpgrade3c
   letAIRun -stop
   playAnimation "TheAvatar" 0x0541ba87 # gen_brainup_admire
   nextState CRG_BrainUpgrade3d
end

state CRG_BrainUpgrade3d
   playAnimation "TheAvatar" 0x055ac811 # gen_brainup_idle_3
   nextState CRG_BrainUpgrade3e
end

state CRG_BrainUpgrade3e
   playAnimation "TheAvatar" 0x05d2bc4c # gen_brainup_react_v3
   nextState CRG_BrainUpgrade3f
end

state CRG_BrainUpgrade3f
   playAnimation "TheAvatar" 0x0559764a # gen_brainup_celebrate_03
   nextState CRG_BrainUpgrade3g
end

state CRG_BrainUpgrade3g
   stopsound music_brain_upgrade
   stopCamera
  pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   nextState CRG_BrainUpgrade3h
end

state CRG_BrainUpgrade3h
   text "Another step towards sentience...  Your brain is larger, your stature grander!  ~br~You can now add a third creature to your pack!" cinematics_crg!0x0541b208
   wait -secs 1
   nextState CRG_BrainUpgrade3i
end

state CRG_BrainUpgrade3i
   wait -forButton
end



####

state CRG_BrainUpgrade4
   description "Brain Upgrade 4"
   addActor "TheAvatar" avatar
   alphaObstacles on -camera -actors "TheAvatar" -radius 8.0 -types all
   letAIRun -avatarOnly
   nextState CRG_BrainUpgrade4a
   startsound music_brain_upgrade -escStop
   startEffect "fadeOut" fade_to_black_quick -noWait
   wait -secs 1   
end

state CRG_BrainUpgrade4a
   letterbox -on
   clearAreaAroundObject "TheAvatar" 10.0 -animals -snap   
   startEffect "fadeIn" fade_from_black_quick -noWait
   nextState CRG_BrainUpgrade4b
   startcamera -target "TheAvatar" -targetHead -orient -offset 7 -useRadius -pitch -.05 -heading 0.5 -fov .8 -snap -noWait
end

state CRG_BrainUpgrade4b
   nextState CRG_BrainUpgrade4c
   wait -forContinue
   startcamera -target "TheAvatar" -targetHead -orient -offset 6 -duration 10 -useRadius -pitch -.05 -heading 0.5 -fov .8 -noWait
end

state CRG_BrainUpgrade4c
   letAIRun -stop
   playAnimation "TheAvatar" 0x0541ba87 # gen_brainup_admire
   nextState CRG_BrainUpgrade4d
end

state CRG_BrainUpgrade4d
   playAnimation "TheAvatar" 0x055ac812 # gen_brainup_idle_4
   nextState CRG_BrainUpgrade4e
end

state CRG_BrainUpgrade4e
   playAnimation "TheAvatar" 0x05d2bc4d # gen_brainup_react_v4
   nextState CRG_BrainUpgrade4f
end

state CRG_BrainUpgrade4f
   playAnimation "TheAvatar" 0x0559764d # gen_brainup_celebrate_04
   nextState CRG_BrainUpgrade4g
end

state CRG_BrainUpgrade4g
   stopsound music_brain_upgrade
   stopCamera
  pauseGame -screenEffect -pauseGraphics
   wait -secs .135
   nextState CRG_BrainUpgrade4h
end

state CRG_BrainUpgrade4h
   text "Another step towards sentience...  Your brain is larger, your stature grander!  ~br~You can now evolve to the tribal phase." cinematics_crg!0x0541b19f
   wait -secs 1
   nextState CRG_BrainUpgrade4i
end

state CRG_BrainUpgrade4i
   wait -forButton
end


# End Brain Upgrade
######################################################################
