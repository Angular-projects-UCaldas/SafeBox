import { Injectable } from '@angular/core';
import { environment } from "src/environments/environment.prod";
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs';
@Injectable({
  providedIn: 'root'
})
export class BoxServiceService {

  constructor(private http: HttpClient) { }

  private apiUrl = environment.endpoint;

  public openBox(bbox: any): Observable<any> {
    let url = this.apiUrl + 'open';
    return this.http.post(url, bbox,{
      headers: new HttpHeaders({
        'Content-Type': 'application/json'
      })
    });
  }

  public status(): Observable<any> {
    let url = this.apiUrl + 'status';
    return this.http.get(url);
  }

  public changePassword(pass: any): Observable<any> {
    let url = this.apiUrl + 'changepassword';
    return this.http.post(url, pass,{
      headers: new HttpHeaders({
        'Content-Type': 'application/json'
      })
    });
  }

  public changeTime(time: any): Observable<any> {
    let url = this.apiUrl + 'changetime';
    return this.http.post(url, time,{
      headers: new HttpHeaders({
        'Content-Type': 'application/json'
      })
    });
  }
}
