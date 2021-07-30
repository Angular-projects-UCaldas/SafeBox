import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoginComponent } from '../home/login/login.component';
import { ControPanelComponent } from './contro-panel/contro-panel.component';
import { HomeModule } from "./home.module";

const routes: Routes = [
  { path: 'login', component: LoginComponent },
  { path: 'controlpanel', component: ControPanelComponent}
];

@NgModule({
  imports: [RouterModule.forChild(routes),
    HomeModule],
  exports: [RouterModule]
})
export class HomeRoutingModule { }
