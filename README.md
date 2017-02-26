# The Augmented Wearables Playground Platform

The AWPP is a HackIllinois open source project which brings excitement to the classic game of hide-and-go-seek. This project is broken into two components: one Android application VirtualHideAndSeek and several nRF51822 Smart Beacons. Using Bluetooth Low Energy signal strength measurements, these devices are notified when they get near each other, allowing the Smart Beacons to display an LED indicating the distance to the phone and the phone to remain notified about all beacons. Thus, the game of hide-and-go-seek is improved by extending the scope of the human eye; the seekers become aware of their surroundings, as do the hiders. The small size of the Smart Beacons makes them perfect to be worn on the wrist or neck. This allows for a dynamic gameplay and at least 6 minutes of fun that never gets old!

## Usage
Get some friends. Suggest playing hide-and-go-seek. Be immediately ostracized. Then, decide who among you will be the seekers and who will be the hider. Give the hider the phone with the app and each of the seekers a tag, and register them using the MAC address and their name. A name is a term used for identification. Names can identify a class or category of things, or a single thing, either uniquely, or within a given context. A personal name identifies, not necessarily uniquely, a specific individual human. The name of a specific entity is sometimes called a proper name (although that term has a philosophical meaning also) and is, when consisting of only one word, a proper noun. Other nouns are sometimes called "common names" or (obsolete) "general names." A name can be given to a person, place, or thing; for example, parents can give their child a name or a scientist can give an element a name. 

The hider can start the game after getting a head start. They will have information on how hot or cold each of the users is, with closer tags being associated with warmer colors. If all of the seekers are cold, it is probably because they ditched the hider and are currently having an awesome time making S'mores around Kevin's new fireplace. It's OK, I'm sure they just forgot about you. I'm sure they'll be back any moment. At least you won hide-and-seek.

## Build/Installation 
For the phone:
  Install and compile the app and run from Android Studio or another IDE.
  
For the beacons:
  Import the project into the [mbed online IDE](https://developer.mbed.org),
  set the target as "Seeed Tiny BLE," and compile.
  Connect the tag to a programmer (such as the nRF51822-DK),
  and drop the .hex file onto the programmer.
  Note that the tag must have a battery inserted in order to program it.
 
## Documentation

Go outside, take 55 paces directly west and then 17 paces southwest. Find the tree marked with a really small "x" on its root. Like, it is tiny. Take an ax and cut down the tree. Don't forget to yell "Timber!" Now, sit on the trunk and pull out your phone. Open this GitHub repository and direct yourself to the html directory for documentation.

## Contributor Guide

See CONTRIBUTORS.md, but Daniel actually did no work and chose to spend the entire hackathon eating bagels and disrupting Purdue students.

## License

I have one of those licenses from Disneyland after going on the Indy 500 ride.

But actually, it's GPL version 3.
