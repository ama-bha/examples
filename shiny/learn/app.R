#
# This is a Shiny web application. You can run the application by clicking
# the 'Run App' button above.
#
# Find out more about building applications with Shiny here:
#
#    http://shiny.rstudio.com/
#

library(shiny)
library(data.table)
library(ggplot2 )
# Define UI for application that draws a histogram
ui <- fluidPage(
    sidebarLayout(
      sidebarPanel(sliderInput("Hello",label = "",min = 0,max=100,step = 1,value=0)
                   , actionButton("GO","GO")
                   ,helpText("Note: while the data view will show only",
                             "the specified number of observations, the",
                             "summary will be based on the full dataset.")),
      mainPanel(
        inputPanel(textInput("AGB","AGB")),
        verbatimTextOutput("info"),
        verbatimTextOutput("info2"),
        tabsetPanel(
          tabPanel("Plot",plotOutput("plot",click = 'plot_click', hover = hoverOpts(id = "plot_hover"))),
          tabPanel("Summary",verbatimTextOutput("summary")),
          tabPanel("Raw",tableOutput("raw"))
        )
      )
    ) 
  

)

# Define server logic required to draw a histogram
server <- function(input, output) {
  df = reactive({
                mtcars=mtcars;
                setDT(mtcars);
                mtcars[mpg < input$Hello]
                }) ;
  
  observeEvent(input$Hello,{print("Hey I changed")});
  output$plot <- renderPlot({
    ggplot(df()) + aes(wt,mpg) + geom_point();
  });
  
  output$info <- renderPrint({
    # With base graphics, need to tell it what the x and y variables are.
    nearPoints(df(), input$plot_click, xvar = "wt", yvar = "mpg")
    # nearPoints() also works with hover and dblclick events
  })
  
  output$raw <- renderTable(df());
  output$summary <- renderText(summary(df()));
  output$info2 <- renderPrint({
    cat("Hover (throttled):\n")
    str(input$plot_hover)
  })
}

# Run the application 
shinyApp(ui = ui, server = server)

