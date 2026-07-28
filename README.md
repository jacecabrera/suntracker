## my WIP sun-tracking solar panel

An ongoing project that I started this summer to try and save us some money by collecting energy from the sun.

## to-do:

v1
- [x] Build general solar panel frame/motor housing
- [ ] Build circuit for bottom electrical box
- [ ] Mount LDR shell on top of solar panel center
- [ ] Wiring
- [ ] Upload code and test (maybe for a week or so) and note down results

v2
- [x] Build stepper motor
- [ ] Replace motor with stepper motor and remove unnecessary sensors

## important information

This is an ongoing work in progress project that I unfortunately won't be able to test and present in time for my Hack the North application.

An important inconsistency between the schematic and my circuit components is that I am running a single [dual H-Bridge DC motor driver](https://www.amazon.ca/H-Bridge-Control-IRF3205-Response-Arduino/dp/B08JM4Z1HP/ref=asc_df_B08JM4Z1HP?mcid=c0fb2f8036e73410ad00a29274b71e2b&tag=googleshopc0c-20&linkCode=df0&hvadid=706747204459&hvpos=&hvnetw=g&hvrand=10131239674028657253&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9001513&hvtargid=pla-1382624912129&psc=1&hvocijid=10131239674028657253-B08JM4Z1HP-&hvexpln=0&gad_source=1) instead of the two separate motor drivers denoted in the schematic. The reason that I had to settle for this workaround in the diagram is simply because I wasn't able to find a suitable component in the Fritzing library nor on their forums (although I was able to find many of the other component files I needed thanks to this forum goat: [vanepp](https://forum.fritzing.org/u/vanepp/summary). Also note that this the first schematic I've made so I apologize for the visual clutter or wiring errors.

<img width="1950" height="1170" alt="circuitSchem" src="https://github.com/user-attachments/assets/221036dc-2471-455d-b07c-ddbe63538fec" />

## processes & how it works

As for information regarding logistics, majority of the **hardware** for the V1 of this project has already been assembled, with the exception of the contents in this repo. At the time of writing this, my pack of [LDR modules](https://www.amazon.ca/dp/B07V3QJ8G2?ref=ppx_yo2ov_dt_b_fed_asin_title) as well as its [electrical housing](https://www.amazon.ca/LeMotech-Junction-Dustproof-Waterproof-Electrical/dp/B07BPPKF2C/ref=sr_1_17?crid=1K7W24JF2E1ER&dib=eyJ2IjoiMSJ9.ZTXkSHMqDhpGk4VsOBfSedtZQGyJJW1bWGDwP15g5ytPUw1pWj3OyCtyrzbAq05T5sNsr1qcX8Hn7M65lRFSefO8IPRNCJOg1ruswT9qJS1g_-mnXt0yIDoV9bvERTWERXJzgRNvXEtxmSPZq9-x-JkSkfwfIO7GYl--WwEMsvdtHdCoNMBUZnvqr2Arc4AGsUAwmTELaFGX7bW4YiKXbZZhj4VHSMy6fYNGMx2DyFYY62PJbWgB7tZbLq3OpEH3HQ8cDo2y9BZDVspaXXruGs7tSlwGmvv4GoOrP8W6sCc.gfXiwqkewKymJkw26IdCU1rUUUwikJD_atdFCu0bxdU&dib_tag=se&keywords=waterproof%2B4%22%2Bplastic%2Bchassis&qid=1785005153&sprefix=waterproof%2B4%2Bplastic%2Bchassis%2Caps%2C146&sr=8-17&th=1) have just arrived today but I don't think I'll have the time to put everything together. Because I am driving a DC motor at the base of the system, I am relying on two endpoint boundaries to prevent the panel from rotating more than 180 degrees on the azimuth. This system consists of 2 sensors at each point and a flag sticking out of the rotating base. When that flag has reached either of the two optical sensors, we should tell the motor to stop and take any necessary action from there. If, for whatever reason this first pass fails, There is a lever behind that point that will essential be pressed back by that flag and again tell it to stop.

The motors are told to rotate based on the readings of 4 different LDR modules in their own respective quadrants located in the solar panel. In essence, the code is rotating along the X or Y axes in order to eliminate the light differences between all 4 sensors, essentially centering the face of the panel to the brightest point it sees. Do note that the code provided above is merely pseudocode, and hasn't been properly tested with the correct hardware and circuitry.

I have begun work on building the stepper motor for the V2, although I probably wont take change any core components until I'm satisfied with the results of the V1 setup.

---

For Hack the North judges, more information and photos regarding the design process are available in an attached google drive in my application.

For everybody else, thank you for checking out my project!

## License

This project is open-source and licensed under the MIT License. See the `LICENSE` file for details.
