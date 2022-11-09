import React, { useEffect, useState } from "react";
import Chart from "chart.js/auto";
import { Chart as Chartjs, LinearScale} from "chart.js";
import { Line } from "react-chartjs-2";

Chartjs.register(
    LinearScale,
)

var apiUrl = "http://127.0.0.1:8000/sensorvalues/"

    
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
            label: 'Values',
            data: [12, 19, 3, 5, 2, 3],
            backgroundColor: [
                'rgba(75,192,192,1)',
            ],
            borderColor: [
                'rgba(0,0,0,1)',
            ],
            borderWidth: 1
        }]
    })


    useEffect(() => {
        const fetchData = async() => {
            const dates = []
            const values = []

            await fetch(apiUrl).then((data) => {
                console.log(data)
                const res = data.json()
                return res
            }).then((res) => {
                console.log(res)

                for(const i of res){
                    dates.push(i.date_registered)
                    values.push(i.value)
                }

                console.log("arrays", dates, values)

                setData({
                    labels: dates,
                    datasets: [{
                        label: 'value',
                        data: values,
                        backgroundColor: [
                            'rgba(75,192,192,1)',
                        ],
                        borderColor: [
                            'rgba(0, 180, 216)',
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
            <Line data={data} height={200} options={options}/>
        </div>
    )
}

export default ShowingData