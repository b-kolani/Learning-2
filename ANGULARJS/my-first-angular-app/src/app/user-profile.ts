import { Component, signal, computed } from '@angular/core';

// user-profile.ts 
@Component({
    selector: 'user-profile',
    template: /*HTML*/ `
        <h1>{{title}}</h1>
        <p>This is user profile page.</p>
        <p>Trial: {{ isTrial() }}</p>
        <p>Expired Trial: {{ isTrialExpired() }}</p>
        <p>Trial Duration: {{ showTrialDuration() }}</p>
        <button (click)="activeTrial()">
            Activet Trial
        </button>
    `,
    styles: /* CSS */`
        h1 {
            font-size: 3em;
        }
    `
})

export class UserProfile {
    title = 'User Profile';
    isTrial = signal(false);
    isTrialExpired = signal(false);
    showTrialDuration = computed(() => this.isTrial() && this.isTrialExpired());

    activeTrial() {
        this.isTrial.set(true);
    }
}