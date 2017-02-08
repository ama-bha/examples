#
# This is a Shiny web application. You can run the application by clicking
# the 'Run App' button above.
#
# Find out more about building applications with Shiny here:
#
#    http://shiny.rstudio.com/
#

library(shiny)
library(leaflet)
ui <- fluidPage(
  leafletOutput("mymap"),
  tags$p(),
  actionButton("recalc","New Points")
  
)

server <- function(input,output,server ) {
  points <- eventReactive(input$recalc,
                          {cbind(rnorm(40)*2+13,rnorm(40)+48)}
                           ,ignoreNULL = FALSE 
                          );
  output$mymap <- renderLeaflet({
    leaflet() %>% addProviderTiles("Stamen.TonerLite",
                                  options=providerTileOptions(noWrap=T)
    ) %>% addMarkers(data=points())
  }
  )
}
# Run the application 
shinyApp(ui = ui, server = server)

