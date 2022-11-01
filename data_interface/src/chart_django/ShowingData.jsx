import React, { useEffect, useState } from "react";
import Chart from "chart.js/auto";
import { Chart as Chartjs, BarElement, CategoryScale, LinearScale} from "chart.js";
import { Bar } from "react-chartjs-2";

Chartjs.register(
    CategoryScale,
    LinearScale,
    BarElement
)

var apiUrl = "http://127.0.0.1:8000/api/sensor/"

    
var options = {
    scales: {
        y: {
            beginAtZero: true
        }
    }
}

const ShowingData = () => {
    const [data, setData] = useState({
        labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],
        datasets: [{
            label: '# of Votes',
            data: [12, 19, 3, 5, 2, 3],
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(153, 102, 255, 0.2)',
                'rgba(255, 159, 64, 0.2)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(153, 102, 255, 1)',
                'rgba(255, 159, 64, 1)'
            ],
            borderWidth: 1
        }]
    })


    useEffect(() => {
        const fetchData = async() => {
            const sensors = []
            const values = []

            await fetch(apiUrl).then((data) => {
                console.log(data)
                const res = data.json()
                return res
            }).then((res) => {
                console.log(res)

                for(const i of res){
                    sensors.push(i.sensor_name)
                    values.push(i.sensor_value)
                }

                console.log("arrays", sensors, values)

                setData({
                    labels: sensors,
                    datasets: [{
                        label: '# of Votes',
                        data: values,
                        backgroundColor: [
                            'rgba(255, 99, 132, 0.2)',
                            'rgba(54, 162, 235, 0.2)',
                            'rgba(255, 206, 86, 0.2)',
                            'rgba(75, 192, 192, 0.2)',
                            'rgba(153, 102, 255, 0.2)',
                            'rgba(255, 159, 64, 0.2)'
                        ],
                        borderColor: [
                            'rgba(255, 99, 132, 1)',
                            'rgba(54, 162, 235, 1)',
                            'rgba(255, 206, 86, 1)',
                            'rgba(75, 192, 192, 1)',
                            'rgba(153, 102, 255, 1)',
                            'rgba(255, 159, 64, 1)'
                        ],
                        borderWidth: 1
                    }]
                })
            }).catch(e => {
                console.log(e)
            })
        }
        fetchData()
    }, [])

    return(
        <div>
            <Bar data={data} height={200} options={options}/>
        </div>
    )
}

export default ShowingData