import { signal, computed } from '@angular/core';

// Create a signal with the `signal` function
const firstname = signal('Morgan');
const firstNameCapitalized = computed(() => firstname().toUpperCase());

// Read a signal value by calling it-- signals are functions.
console.log(firstname());
console.log(firstNameCapitalized());

// Change the value of this signal by calling its `set`
// method with a new value. 
firstname.set('Biman');
console.log(firstname());
console.log(firstNameCapitalized());

// We can also use the `update` method to change the value 
// based on the previuous value. 
firstname.update((name) => name.toUpperCase());
console.log(firstname());