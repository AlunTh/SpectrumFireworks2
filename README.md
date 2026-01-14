SpectrumFireworks2
=====

[Open this project in 8bitworkshop](http://8bitworkshop.com/redir.html?platform=zx&githubURL=https%3A%2F%2Fgithub.com%2FAlunTh%2FSpectrumFireworks2&file=main.c).

Fireworks show written in C for the ZX Spectrum.

Intended as a birthday or new-year e-card, but not finished in time this year (end 2025).

Possible future enhancements:

Ability to generate a string of timed fireworks that explode in the pattern of particular strings (eg. so it can spell out "happy birthday" or the year).

Alternative way of colouring cells: have a defined sequence of colour+bright values that a cell fades through after being set to the brightest, gradually falling back to the dimmest.
Possible sequence:
	bright 1 ink 7 - bright white 71
	bright 1 ink 5 - bright cyan  69
	bright 0 ink 5 - cyan          5
	bright 1 ink 1 - bright blue  65
	bright 0 ink 1 - blue          1



The random spawn should sometimes spawn back to the initial "show".

The chained expiry function generates so many fireworks it produces a slowdown - it should also only be used where the firework will detonate sufficiently high up on the screen.

For new year's usage, can we use the interrupt system for an approximate clock ?
