import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { MatSnackBar } from "@angular/material/snack-bar";
import { environment } from "src/environments/environment.prod";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  constructor(private router: Router, private _snackBar: MatSnackBar) { }
  email : string = "";
  password : string = "";
  error: boolean = false;
  hide = true;
  ngOnInit(): void {
    console.log();
  }

  public login() {
    if(this.email == environment.email && this.password == environment.password) {
      this.router.navigate(['/controlpanel']);
    }else this.openSnackBar("Wrong Password", "Dissmis");
  }

  openSnackBar(message: string, action: string) {
    this._snackBar.open(message, action, {
      duration: 5000,
    });
  }
}
