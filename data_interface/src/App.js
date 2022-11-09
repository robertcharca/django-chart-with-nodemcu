
import './App.css';
import ShowingData from './chart_django/ShowingData';

function App() {
  return (
    <div className="App">
      <nav class="navbar navbar-dark bg-dark">
        <div class="container-fluid">
          <span class="navbar-brand mb-0 h1">Charts</span>
        </div>
      </nav>

      <h3 style={{margin:30}}>Data from temperature sensor</h3>

      <div style={{height: 900, width: 900, margin:"auto"}}>
        <ShowingData />
      </div>
      
    </div>
  );
}

export default App;
