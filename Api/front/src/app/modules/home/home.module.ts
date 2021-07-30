import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { LoginComponent } from './login/login.component';
import { MaterialModule } from "../material/material.module";
import { FormsModule } from "@angular/forms";
import { ControPanelComponent } from './contro-panel/contro-panel.component';

@NgModule({
  declarations: [
    LoginComponent,
    ControPanelComponent
  ],
  imports: [
    CommonModule,
    MaterialModule,
    FormsModule
  ]
})
export class HomeModule { }
