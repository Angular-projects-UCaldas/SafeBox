import { Component, OnInit } from '@angular/core';
import { MatSnackBar } from "@angular/material/snack-bar";
import { BoxServiceService } from 'src/app/services/box-service.service';
export interface Status {
  status: string;
}
@Component({
  selector: 'app-contro-panel',
  templateUrl: './contro-panel.component.html',
  styleUrls: ['./contro-panel.component.css']
})

export class ControPanelComponent implements OnInit {

  constructor(private _snackBar: MatSnackBar,
      private _boxService: BoxServiceService
    ) { }

  actions: string[] = ['Open Box', 'Change Password', 'Change Time', 'Log'];
  selectedOption: string = "";
  open: boolean = false;
  chPassword: boolean = false;
  chText: boolean = false;
  execute: boolean = true;
  log: boolean = false;
  passwordFront: string = "";
  timeFront: number = 0;
  statusList: Status[] = [];
  displayedColumns: string[] = ['status'];
  dataSource = this.statusList;
  ngOnInit(): void {
    this.getLog();
  }

  public change(){
    if(document.getElementById("option")?.innerHTML == "Open Box"){
      this.open = true;
      this.execute = false;
    }
    else if(document.getElementById("option")?.innerHTML == "Change Password"){
      this.chPassword = true;
      this.execute = false;
    }
    else if(document.getElementById("option")?.innerHTML == "Change Time"){
      this.chText = true;
      this.execute = false;
    }
    else if(document.getElementById("option")?.innerHTML == "Log"){
      this.log = true;
      this.execute = false;
    }
  }

  public reset(){
    setTimeout(() => {
      this.execute = true;
      this.open = false;
      this.chPassword = false;
      this.chText = false;
    } , 10000);

  }
  
  openSnackBar(message: string, action: string) {
    this._snackBar.open(message, action, {
      duration: 5000,
    });
  }

  public openBox(){
    let event = {
      text : "openBox",
    }
    this._boxService.openBox(event)
    .subscribe((response)=> {
      console.log(response);
    });
    this.openSnackBar("Box opened", "Close");
    this.reset();
  }

  public changePassword(){
    let password = {
      text : "changePassword",
      data : ("2" + this.passwordFront)
    };
    this._boxService.changePassword(password)
    .subscribe((response)=> {
      console.log(response);
    });
    this.chPassword = false;
    this.openSnackBar("Password changed", "Close");
    this.reset();
  }

  public changeTime(){
    let time = {
      text : "changeTime",
      data : ("3" + this.timeFront)
    };
    this._boxService.changePassword(time)
    .subscribe((response)=> {
      console.log(response);
    });
    this.chText = false;
    this.openSnackBar("Time changed", "Close");
    this.reset();
  }

  public viewLog(){
    
    this.log = false;
    this.getLog();
    this.reset();
  }

  public getLog(){
    this._boxService.status()
    .subscribe((response)=> {
      this.statusList = response.data;
    });
    setTimeout(() => {
      this.closeLog();
    } , 10000);
  }

  public closeLog(){
    this.execute = true;
    this.open = false;
    this.chPassword = false;
    this.chText = false;
    this.log = false;
    this.statusList = [];
  }
}
