
import './App.css';
import ShowingData from './chart_django/ShowingData';

function App() {
  return (
    <div className="App">
      <nav class="navbar navbar-dark bg-dark">
        <div class="container-fluid">
          <span class="navbar-brand mb-0 h1">Navbar</span>
        </div>
      </nav>

      <div style={{height: 850, width: 850}}>
        <ShowingData />
      </div>
      
    </div>
  );
}

export default App;
