
window.onload = function() {

                                var ctx = document.getElementById('myChartbar').getContext('2d');
                                
                                var myChart = new Chart(ctx, {
                                            type: 'bar',
                                            data: {
                                                labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],
                                                datasets: [{
                                                    label: '# of Votes',
                                                    fill:true,
                                                    data: [12, 19, 3, 5, 2, 3],
                                                    backgroundColor: [
                                                        'rgba(255, 99, 132, 0.5)',
                                                        'rgba(54, 162, 235, 0.5)',
                                                        'rgba(255, 206, 86, 0.5)',
                                                        'rgba(75, 192, 192, 0.5)',
                                                        'rgba(153, 102, 255, 0.5)',
                                                        'rgba(255, 159, 64, 0.5)'
                                                    ],
                                                    borderColor: [
                                                        'rgba(255, 99, 132, 1)',
                                                        'rgba(54, 162, 235, 1)',
                                                        'rgba(255, 206, 86, 1)',
                                                        'rgba(75, 192, 192, 1)',
                                                        'rgba(153, 102, 255, 1)',
                                                        'rgba(255, 159, 64, 1)'
                                                    ],
                                                    borderWidth:2,
                                                    hoverBorderColor:'#444'
                                                }]
                                            },
                                            options: {
                                                title:
                                                {
                                                display:false,
                                                text:'# of votes',
                                                fontSize:15,
                                                fontColor:'grey'
                                                },
                                                scales: {
                                                    yAxes: [{
                                                        ticks: {
                                                            beginAtZero: true
                                                                }
                                                            }]
                                                        },
                                                responsive:true,
                                                maintainAspectRation:false
                            
                                                    }
                                            });



                            var ctx = document.getElementById('myChartline').getContext('2d');
                            var myChart = new Chart(ctx, {
                                        type: 'line',
                                        data: {
                                            labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],
                                            datasets: [{
                                                label: '# of Votes',
                                                fill:true,
                                                lineTension:.2,
                                                data: [12, 19, 3, 5, 2, 3],
                                                pointbackgroundColor: [
                                                    'rgba(255, 99, 132, 0.5)',
                                                    'rgba(54, 162, 235, 0.5)',
                                                    'rgba(255, 206, 86, 0.5)',
                                                    'rgba(75, 192, 192, 0.5)',
                                                    'rgba(153, 102, 255, 0.5)',
                                                    'rgba(255, 159, 64, 0.5)'
                                                ],
                                                borderColor: [
                                                    'rgba(255, 99, 132, 1)',
                                                    'rgba(54, 162, 235, 1)',
                                                    'rgba(255, 206, 86, 1)',
                                                    'rgba(75, 192, 192, 1)',
                                                    'rgba(153, 102, 255, 1)',
                                                    'rgba(255, 159, 64, 1)'
                                                ],
                                                borderWidth:2,
                                                hoverBorderColor:'#444'
                                            }]
                                        },
                                        options: {
                                                    title:
                                                    {
                                                        display:false,
                                                        text:'# of votes',
                                                        fontSize:15,
                                                        fontColor:'grey'
                                                    },
                                                    scales: {
                                                        yAxes: [{
                                                            ticks: {
                                                                beginAtZero: true
                                                                    }
                                                                }]
                                                            },
                                                    responsive:true,
                                                    maintainAspectRation:false
                        
                                                }
                                        });

                            
                       
            

                            var ctx = document.getElementById('myChartdoughnut').getContext('2d');
                            var myChart = new Chart(ctx, {
                                        type: 'doughnut',
                                        data: {
                                            labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],
                                            datasets: [{
                                                label: '# of Votes',
                                                data: [12, 19, 3, 5, 2, 3],
                                                backgroundColor: [
                                                    'rgba(255, 99, 132, 0.5)',
                                                    'rgba(54, 162, 235, 0.5)',
                                                    'rgba(255, 206, 86, 0.5)',
                                                    'rgba(75, 192, 192, 0.5)',
                                                    'rgba(153, 102, 255, 0.5)',
                                                    'rgba(255, 159, 64, 0.5)'
                                                ],
                                                borderColor: [
                                                    'rgba(255, 99, 132, 1)',
                                                    'rgba(54, 162, 235, 1)',
                                                    'rgba(255, 206, 86, 1)',
                                                    'rgba(75, 192, 192, 1)',
                                                    'rgba(153, 102, 255, 1)',
                                                    'rgba(255, 159, 64, 1)'
                                                ],
                                               
                                                borderWidth:2,
                                                hoverBorderColor:'#444'
                                            }]
                                        },
                                        options: {
                                                    
                                                    title:
                                                    {
                                                        display:false,
                                                        text:'# of votes',
                                                        fontSize:15,
                                                    },
                                                    legend:
                                                        {
                                                            position:'right',
                                                        },
                                                    scales: {
                                                        yAxes: [{
                                                                    display:false,
                                                                    stacked:true,
                                                                    ticks: {
                                                                        beginAtZero: true
                                                                            },
                                                                    gridLines:
                                                                    {
                                                                        display:false,
                                                                    },
                                                                }],
                                                        xAxes:  [{
                                                                    display:false,
                                                                    
                                                                }]    
                                                            },

                                                    responsive:true,
                                                    maintainAspectRation:false
                                            
                                                }
                                        });

                                    
                                        
}