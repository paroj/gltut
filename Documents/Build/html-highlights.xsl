<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:d="http://docbook.org/ns/docbook" xmlns:xslthl="http://xslthl.sf.net"
    exclude-result-prefixes="xslthl d" version="1.0">

    <xsl:import href="common-highlights.xsl"/>

    <xsl:template match="xslthl:keyword" mode="xslthl">
        <span class="code-keyword">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:basic-type" mode="xslthl">
        <span class="code-type">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:type-modifier" mode="xslthl">
        <span class="code-modifier">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:sampler-type" mode="xslthl">
        <span class="code-sampler">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>
    
    <xsl:template match="xslthl:library-func" mode="xslthl">
        <span class="code-function">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>
    
    <xsl:template match="xslthl:string" mode="xslthl">
        <span class="code-string">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:comment" mode="xslthl">
        <span class="code-comment">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:directive" mode="xslthl">
        <span class="code-directive">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:tag" mode="xslthl">
        <span class="code-tag">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:attribute" mode="xslthl">
        <span class="code-attribute">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:value" mode="xslthl">
        <span class="code-value">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:html" mode="xslthl">
        <span class="code-html">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:xslt" mode="xslthl">
        <span class="code-xslt">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:number" mode="xslthl">
        <span class="code-number">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <xsl:template match="xslthl:annotation" mode="xslthl">
        <span class="code-annotation">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

    <!-- Not sure which element will be in final XSLTHL 2.0 -->
    <xsl:template match="xslthl:doccomment|xslthl:doctype" mode="xslthl">
        <span class="code-tag">
            <xsl:apply-templates mode="xslthl"/>
        </span>
    </xsl:template>

</xsl:stylesheet>
