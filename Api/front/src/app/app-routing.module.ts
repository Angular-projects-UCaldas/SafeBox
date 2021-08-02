import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HomeRoutingModule } from './modules/home/home-routing.module';

const routes: Routes = [
  { path: '**', redirectTo: '/login' }
];

@NgModule({
  imports: [RouterModule.forRoot(routes),
  HomeRoutingModule],
  exports: [RouterModule]
})
export class AppRoutingModule { }
