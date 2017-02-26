# The Augmented Wearables Playground Platform

The AWPP is a HackIllinois open source project which brings excitement to the classic game of hide and go seek. This project is broken into two componenets, one Android application VirtualHideAndSeek and NRF51822 smart beacons  smart beacons. Using bluetooth RSSI values, these devices are notified when the get near to each other, allowing the smart beacons to display an LED approximating the distance to the phone and the phone remain notified about all beacons. Thus, the game of hide and go seek is improved by extending the scope of the human eye; the chasers become aware of their surroundings, as do the hiders. The small nature of the smart beacons makes them perfect to be worn on the wrist or neck. This allows for a dynamic gameplay and at least 6 minutes of fun that never gets old!

## Usage
Get some friends. Suggest playing hide and go seek. Be immediately ostricized. Then, decide who among you will be the chasers and who will be the hider. Give the hider the phone with the app and each of the chasers a tag and register them using the MAC addresss and their name. A name is a term used for identification. Names can identify a class or category of things, or a single thing, either uniquely, or within a given context. A personal name identifies, not necessarily uniquely, a specific individual human. The name of a specific entity is sometimes called a proper name (although that term has a philosophical meaning also) and is, when consisting of only one word, a proper noun. Other nouns are sometimes called "common names" or (obsolete) "general names". A name can be given to a person, place, or thing; for example, parents can give their child a name or a scientist can give an element a name. 

The chased can start the game after getting a head start. They will have information on how hot or cold each of the users is, with closer tags being associated with warmer colors. If all of the chasers are cold, it is probably because they ditched the hider and are currently having an awesome time making Smores around Kevin's new fireplace. It's ok, I'm sure they just forgot about you. I'm sure they'll be back any moment. At least you won hide and seek.

## Build/Installation 
For the phone:
  Install and compile the app and run from AndroidStudio or another IDE.
  
For the beacons:
  Import the project into the [mbed online IDE](https://developer.mbed.org),
  set the target as "Seeed Tiny BLE," and compile.
  Connect the tag to a programmer (such as the nRF51822-DK),
  and drop the .hex file onto the programmer.
  Note that the tag must have a battery inserted in order to program it.
 
 ## Documentation
 Go outside, take 55 paces directly west then take 17 paces southwest. Find the tree marked with a small "x" on its root. Take an ax and cut down the tree. Now, sit on the trunk and pull out your phone. Open this github repository and direct yourself to the html directory for documentation.
 
 ## Contributor Guide
 See contributors.md, but Daniel actually did no work and chose to spend the entire Hackathon eating bagels and disrupting Purdue students.
 
 ## Licence
 I have one of those licences from Disneyland after going on the Indy 500 track.

 But actually, it's GPL version 3.
