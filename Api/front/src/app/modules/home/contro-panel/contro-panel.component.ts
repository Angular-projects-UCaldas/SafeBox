import { Component, OnInit } from '@angular/core';
import { FormControl } from "@angular/forms";

@Component({
  selector: 'app-contro-panel',
  templateUrl: './contro-panel.component.html',
  styleUrls: ['./contro-panel.component.css']
})
export class ControPanelComponent implements OnInit {

  constructor() { }

  actions: string[] = ['Open Box', 'Change Password', 'Change Time'];
  selectedOption: string = "";
  open: boolean = false;
  password: string = "";
  ngOnInit(): void {

  }

  public change(){
    if(document.getElementById("option")?.innerHTML == "Open Box"){
      this.open = true;
    }
  }
}
